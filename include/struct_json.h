#ifndef _H_JSON
#define _H_JSON

#include <data/json.h>

typedef struct {
    int x;
    int y;
} location_t;

const struct json_obj_descr location_descr[] = {
    JSON_OBJ_DESCR_PRIM(location_t, x, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(location_t, y, JSON_TOK_NUMBER),
};

typedef struct {
    char *name;
    location_t location;
} sensor_t;

const struct json_obj_descr sensor_descr[] = {
    JSON_OBJ_DESCR_PRIM(sensor_t, name, JSON_TOK_STRING),
    JSON_OBJ_DESCR_OBJECT(sensor_t, location, location_descr),
};

typedef struct {
    int time;

    int temperature;
    int pressure;
    int speed;

    sensor_t sensor;
} measurement_t;

const struct json_obj_descr measurement_descr[] = {
    JSON_OBJ_DESCR_PRIM(measurement_t, time, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(measurement_t, temperature, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(measurement_t, pressure, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_PRIM(measurement_t, speed, JSON_TOK_NUMBER),
    JSON_OBJ_DESCR_OBJECT(measurement_t, sensor, sensor_descr),
};

typedef struct  {
    measurement_t measurements[5];
    size_t count;
} measurements_list_t;

const struct json_obj_descr measurements_list_desc[] = {
    JSON_OBJ_DESCR_OBJ_ARRAY(measurements_list_t, measurements, 5, count, measurement_descr, ARRAY_SIZE(measurement_descr)),
};



void json_show_sizes(void);

void json_do_buf(void);

void json_do_cb(void);

#endif