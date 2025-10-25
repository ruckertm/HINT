Name: hintview
Version: 2.3.0
Release: 1%{?dist}
Summary: HintView for Linux (GTK)
License: GPLv2.1
Packager: Andreas Scherer <https://ascherer.github.io/>

URL: https://hint.userweb.mwn.de/hint/%{name}.html
Source0: https://github.com/ruckertm/HINT/releases/%{name}-%{version}.tar.gz

%if "%{_vendor}" == "debbuild"
BuildRequires: gir1.2-freedesktop-dev gir1.2-glib-2.0-dev icu-devtools
BuildRequires: libatk-bridge2.0-dev libatk1.0-dev libatspi2.0-dev libblkid-dev
BuildRequires: libcairo2-dev libdatrie-dev libdbus-1-dev libdeflate-dev
BuildRequires: libepoxy-dev libfribidi-dev libgdk-pixbuf-2.0-dev libglib2.0-dev
BuildRequires: libglib2.0-dev-bin libgraphite2-dev libgtk-3-dev libharfbuzz-dev
BuildRequires: libice-dev libicu-dev libjbig-dev libjpeg-dev libjpeg-turbo8-dev
BuildRequires: libjpeg8-dev liblerc-dev liblzma-dev libmount-dev
BuildREquires: libpango1.0-dev libpcre2-dev libpixman-1-dev libselinux1-dev
BuildRequires: libsepol-dev libsharpyuv-dev libsm-dev libthai-dev libtiff-dev
BuildRequires: libwebp-dev libxcb-render0-dev libxcb-shm0-dev libxcomposite-dev
BuildRequires: libxdamage-dev libxft-dev libxkbcommon-dev libxtst-dev
BuildRequires: libzstd-dev
Requires: gir1.2-atspi-2.0 libcairo-script-interpreter2 libgirepository-2.0-0
Requires: libglib2.0-bin libharfbuzz-cairo0 libpcre2-posix3 libtiffxx6
Requires: libwebpdecoder3 pango1.0-tools wayland-protocols
%endif

%description
The HintView program for Linux with GTK interface.

%prep
%autosetup -c

%build
cd %{name}/Linux
make

%install
cd %{name}/Linux
strip hintview
%{__rm} -rf %{buildroot}
%{__install} -d %{buildroot}%{_bindir} \
    %{buildroot}%{_datadir}/glib-2.0/schemas
%{__install} -t %{buildroot}%{_bindir} --mode=755 hintview
%{__install} -t %{buildroot}%{_datadir}/glib-2.0/schemas \
    edu.hm.cs.hintview.gschema.xml

%files
%{_bindir}/%{name}
%{_datadir}/glib-2.0/schemas/edu.hm.cs.hintview.gschema.xml

%post
glib-compile-schemas %{_datadir}/glib-2.0/schemas/

%postun
glib-compile-schemas %{_datadir}/glib-2.0/schemas/

%changelog
* Sun Oct 12 2025 Andreas Scherer <https://ascherer.github.io>
- HintView/GTK package
