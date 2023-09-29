Name: hintview
Version: 1.3.1
Release: 1%{?dist}
Summary: Hintview for Linux
License: GPLv3+

URL: https://hint.userweb.mwn.de/hint/%{name}.html
Source0: https://github.com/ruckertm/HINT/eleases/%{name}-%{version}.tar.gz

#BuildRequires:
#Requires:

%description
The Hintview program for Linux.

%prep
%autosetup -c

%build
cd %{name}/Linux
make

%install
cd %{name}/Linux
%make_install

%files
%license LICENSE
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1

%changelog
* Fri Sep 29 2023 Andreas Scherer <https://ascherer.github.io>
- First Hintview package
