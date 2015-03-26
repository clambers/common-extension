Name:     common-extension
Summary:  A native Tizen extension providing JLR common assets
Version:  0.0.1
Release:  1
Group:    Applications/Native Applications
License:  LGPL-3.0
URL:      http://www.tizen.org
Source:   %{name}-%{version}.tar.gz

%define debug_package %{nil}

%description
libcommon is a native Tizen extension containing all JLR assets. It exposes a
simple interface to reach these assets in a generic way.

%prep
%autosetup

%build
%autogen
%configure
make %{?_smp_mflags}

%install
%make_install

%check
make %{?_smp_mflags} check

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%license COPYING COPYING.LESSER
%doc README.md
%{_includedir}/common.h
%{_libdir}/libcommon.so*
%{_libdir}/libcommon.a
%{_datadir}/pkgconfig/common.pc
