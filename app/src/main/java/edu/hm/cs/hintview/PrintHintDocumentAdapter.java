package edu.hm.cs.hintview;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.pdf.PdfDocument;
import android.os.Bundle;
import android.os.CancellationSignal;
import android.os.ParcelFileDescriptor;
import android.print.PageRange;
import android.print.PrintAttributes;
import android.print.PrintDocumentAdapter;
import android.print.PrintDocumentInfo;
import android.print.pdf.PrintedPdfDocument;

import java.io.FileOutputStream;
import java.io.IOException;

// following https://www.techotopia.com/index.php/An_Android_Custom_Document_Printing_Tutorial

public class PrintHintDocumentAdapter extends PrintDocumentAdapter {
    Context context;
    private int width, height; // page dimension in pixel
    private int width_Mils, height_Mils; // page dimension in 1/1000 inch
    private double xdpi,ydpi;
    private String name;
    private PrintDocumentInfo info;
    public PdfDocument hintDocument;
    private CancellationSignal.OnCancelListener doCancel;
    private boolean canceled;

    public PrintHintDocumentAdapter(Context context, String fileUriString) {
        this.context=context;
        width=-1;
        height=-1;
        xdpi=-1.0;
        xdpi=-1.0;
        name = fileUriString;
        if (name.endsWith(".hnt"))
            name = name.substring(0, name.length() - 4);
        name = "HINT_print.pdf"; // name+".pdf";
        info = new PrintDocumentInfo
                .Builder(name)
                .setContentType(PrintDocumentInfo.CONTENT_TYPE_DOCUMENT)
                .setPageCount(PrintDocumentInfo.PAGE_COUNT_UNKNOWN)
                .build();
        doCancel = new CancellationSignal.OnCancelListener() {
            @Override
            public void onCancel() {
                canceled=true;
            }
        };
    }

    @Override
    public void onStart() {
        super.onStart();
        canceled=false;
    }

    @Override
    public void onLayout(PrintAttributes oldAttributes, PrintAttributes newAttributes, CancellationSignal cancellationSignal, LayoutResultCallback callback, Bundle extras) {
        width_Mils = newAttributes.getMediaSize().getWidthMils(); // width in 1/1000 inch
        height_Mils = newAttributes.getMediaSize().getHeightMils(); // height in 1/1000 inch
        double x = newAttributes.getResolution().getHorizontalDpi();
        double y = newAttributes.getResolution().getVerticalDpi();

        cancellationSignal.setOnCancelListener(doCancel);
        int w = (int)Math.round(width_Mils*x/1000.0);
        int h = (int)Math.round(height_Mils*y/1000.0);
        hintDocument = new PrintedPdfDocument(context, newAttributes);
        if (cancellationSignal.isCanceled())
            callback.onLayoutCancelled();
        else if (w==width && h==height && x==xdpi && y==ydpi)
           callback.onLayoutFinished(info, false);
        else {
            width = w;
            height = h;
            xdpi = x;
            ydpi = y;
            HINTVIEWLib.change(width, height, xdpi, ydpi);
            callback.onLayoutFinished(info, true);
        }
    }


    @Override
    public void onWrite(PageRange[] pages, ParcelFileDescriptor destination, CancellationSignal cancellationSignal, WriteResultCallback callback) {
        cancellationSignal.setOnCancelListener(doCancel);

        for (int i = 0; i < 4; i++) {
            if (pageInRange(pages, i))
            {
                PdfDocument.PageInfo newPage = new PdfDocument.PageInfo.Builder((int)Math.round(width_Mils*72.27/1000.0),(int)Math.round(height_Mils*72.27/1000.0), i).create();

                PdfDocument.Page page = hintDocument.startPage(newPage);

                if (cancellationSignal.isCanceled()) {
                    callback.onWriteCancelled();
                    hintDocument.close();
                    hintDocument = null;
                    return;
                }
                drawPage(page, i+1); // page numbers start at 1
                hintDocument.finishPage(page);
            }
        }

        try {
            hintDocument.writeTo(new FileOutputStream(
                    destination.getFileDescriptor()));
        } catch (IOException e) {
            callback.onWriteFailed(e.toString());
            return;
        } finally {
            hintDocument.close();
            hintDocument = null;
        }
        callback.onWriteFinished(pages);
    }

    private boolean pageInRange(PageRange[] pageRanges, int page)
    {
        for (int i = 0; i<pageRanges.length; i++)
        {
            if ((page >= pageRanges[i].getStart()) &&
                    (page <= pageRanges[i].getEnd()))
                return true;
        }
        return false;
    }

    private void drawPage(PdfDocument.Page page,
                          int pagenumber) {
        Canvas canvas = page.getCanvas();

        int w = canvas.getWidth(); // width in pixel. Einheit scheinbar  pt
        int h = canvas.getHeight(); // height in pixel.
        int r = canvas.getDensity(); // Einheit unklar.

        int titleBaseLine = h/5;
        int leftMargin = w/10;
        int w_pt = page.getInfo().getPageWidth(); // width in pt
        int h_pt = page.getInfo().getPageHeight(); // Heigth in pt


        Paint paint = new Paint();


        if (pagenumber % 2 == 0)
            paint.setColor(Color.RED);
        else
            paint.setColor(Color.GREEN);

        canvas.drawCircle(w/2,
                h/2,
                w/2,
                paint);

        paint.setColor(Color.BLUE);
        paint.setTextSize(42); // 42 pt

        canvas.drawText(
                "Test Page " + pagenumber,
                (float)leftMargin,
                (float)titleBaseLine,
                paint);

    }


    @Override
    public void onFinish() {
        super.onFinish();
    }


}
