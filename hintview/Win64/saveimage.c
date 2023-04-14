#include <windows.h>
#include "basetypes.h"
#include "error.h"
#include "winmain.h"
#include "saveimage.h"



/* the following code uses the article "Storing an Image" from https://msdn.microsoft.com/ */
static PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 

    // Retrieve the bitmap color format, width, and height.  
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        hint_message("GetObject","Unable to retrieve bitmap information"); 

    // Convert the color format to a count of bits.  
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure  
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
    // data structures.)  

     if (cClrBits < 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 

	 if (pbmi==NULL)
	 { hint_message("Write Bitmap File", "Unable to allocate memory");
	   return NULL;
	 }

    // Initialize the fields in the BITMAPINFO structure.  

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

    // If the bitmap is not compressed, set the BI_RGB flag.  
    pbmi->bmiHeader.biCompression = BI_RGB; 

    // Compute the number of bytes in the array of color  
    // indices and store the result in biSizeImage.  
    // The width must be DWORD aligned unless the bitmap is RLE 
    // compressed. 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the  
    // device colors are important.  
     pbmi->bmiHeader.biClrImportant = 0; 
     return pbmi; 
 } 


static int CreateBMPFile(LPTSTR pszFile,  HBITMAP hBMP, HDC hDC) 
 { 
    HANDLE hf;                 // file handle  
    BITMAPFILEHEADER hdr;       // bitmap file-header  
    PBITMAPINFOHEADER pbih;     // bitmap info-header  
    LPBYTE lpBits;              // memory pointer  
    DWORD dwTmp; 
	int ok=1;
    PBITMAPINFO pbi;
	
	pbi= CreateBitmapInfoStruct(hBMP);
	if (pbi==NULL) return 0;

    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits) 
	{  hint_message("Write Bitmap File", "Unable to allocate memory while writing bitmap file");
	   ok=0;
	   goto free_memory;;
	}

    // Retrieve the color table (RGBQUAD array) and the bits  
    // (array of palette indices) from the DIB.  
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS)) 
	{  hint_message("Write Bitmap File", "Unable to get bits while writing bitmap file");
	   ok=0;
	   goto free_memory;
	}
    // Create the .BMP file.  
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) 
	{  hint_message("Write Bitmap File", "Unable to open file while writing bitmap file");
	   ok=0;
	   goto free_memory;
	}
    hdr.bfType = ('M'<<8)|'B';    
     // Compute the offset to the array of color indices.  
    hdr.bfOffBits = sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed*sizeof(RGBQUAD); 
   // Compute the size of the entire file.  
    hdr.bfSize = hdr.bfOffBits + pbih->biSizeImage; 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
    // Copy the BITMAPFILEHEADER into the .BMP file.  
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL)) 
	{  hint_message("Write Bitmap File", "Unable to write bitmap file"); 
	   ok=0;
	   goto close_file;
	}

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, ( NULL)))
	{  hint_message("Write Bitmap File", "Unable to write bitmap file"); 
	   ok=0;
	   goto close_file;
	}

    // Copy the array of color indices into the .BMP file.  
    if (!WriteFile(hf, (LPSTR) lpBits, (int)pbih->biSizeImage, (LPDWORD) &dwTmp,NULL)) 
	{  hint_message("Write Bitmap File", "Unable to write bitmap file"); 
	   ok=0;
	   goto close_file;
	}

close_file:
     if (!CloseHandle(hf)) 
	 { hint_message("Write Bitmap File", "Unable to close bitmap file"); 
	   ok=0;
	 }

free_memory:  
	if (pbi!=NULL) LocalFree(pbi);
    if (lpBits!=NULL) GlobalFree((HGLOBAL)lpBits);
	return ok;
}



void write_bmp(char *filename)
{ HDC hDCmem = CreateCompatibleDC(hDCMain); 
  HBITMAP hBMPmem = CreateCompatibleBitmap(hDCMain, client_width, client_height); 
  HBITMAP hOld=(HBITMAP)SelectObject(hDCmem, hBMPmem); 
  BitBlt(hDCmem, 0, 0, client_width, client_height, hDCMain, 0, 0, SRCCOPY);
  CreateBMPFile(filename, hBMPmem, hDCmem);
  SelectObject(hDCmem, hOld); 
  DeleteObject(hBMPmem); 
  DeleteDC(hDCmem);
}
