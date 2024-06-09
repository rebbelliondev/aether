#pragma once
#include <stddef.h>

enum Vendor {
    AMD,
    AMD_OLD,
    INTEL,
    VIA,
    TRANSMETA,
    TRANSMETA_OLD,
    CYRIX,
    CENTAUR,
    NEXGEN,
    UMC,
    SIS,
    NSC,
    RISE,
    VORTEX,
    A0486,
    A0486_OLD,
    ZHAOXIN,
    HYGON,
    ELBRUS,

    QEMU,
    KVM,
    VMWARE,
    VIRTUALBOX,
    XEN,
    HYPERV,
    PARRALES,
    BHYVE,
    QNX
};

class CpuIdDriver {
public:
    CpuIdDriver();

    char* vendor();
};

extern CpuIdDriver cpuid;