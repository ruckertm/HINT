Name: hintview
Version: 2.1.0
Release: 1%{?dist}
Summary: Hintview for Linux
License: GPLv2.1
Packager: Andreas Scherer <https://ascherer.github.io/>

URL: https://hint.userweb.mwn.de/hint/%{name}.html
Source0: https://github.com/ruckertm/HINT/eleases/%{name}-%{version}.tar.gz

%if "%{_vendor}" == "debbuild"
BuildRequires: libegl-dev libegl1-mesa-dev libffi-dev
BuildRequires: libgl-dev libgl1-mesa-dev libgles-dev
BuildRequires: libglew-dev libglfw3-dev libglu1-mesa-dev
BuildRequires: libglvnd-core-dev libglvnd-dev libglx-dev
BuildRequires: libopengl-dev libvulkan-dev libwayland-bin
BuildRequires: libwayland-dev libxcursor-dev libxext-dev
BuildRequires: libxfixes-dev libxi-dev libxinerama-dev
BuildRequires: libxrandr-dev libxrender-dev
Requires: libglew2.2 libglfw3
%endif

%description
The Hintview program for Linux.

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
	%{buildroot}%{_mandir}/man1
%{__install} -t %{buildroot}%{_bindir} --mode=755 hintview
%{__install} -t %{buildroot}%{_mandir}/man1 --mode=644 hintview.1

%files
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1.gz

%changelog
* Fri Sep 29 2023 Andreas Scherer <https://ascherer.github.io>
- First Hintview package
