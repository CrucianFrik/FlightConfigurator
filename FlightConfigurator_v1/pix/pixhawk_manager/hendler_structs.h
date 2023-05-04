#ifndef HENDLER_STRUCTS_H
#define HENDLER_STRUCTS_H

struct ParamInfo{
        char param_id[16];
        uint16_t param_type;
        float param_value;
};

enum ConnectionStatus{
    none,
    successful,
    failed
};

#endif // HENDLER_STRUCTS_H
