#ifndef HENDLER_STRUCTS_H
#define HENDLER_STRUCTS_H

struct ParamInfo{
        char param_id[17];
        uint16_t param_type;
        float param_value;
};

enum ConnectionStatus{
    none,
    successful,
    failed
};

struct GPSPoint{
    float lat;
    float lon;
    float alt;
};

#endif // HENDLER_STRUCTS_H
