#include "struct_json.h"

#include "errno.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(json, LOG_LEVEL_DBG);


void json_show_sizes(void)
{
    LOG_INF("sizeof(struct location_t) = %d", sizeof(location_t));
    LOG_INF("sizeof(struct sensor_t) = %d", sizeof(sensor_t));
    LOG_INF("sizeof(struct measurement_t) = %d", sizeof(measurement_t));
    LOG_INF("sizeof(struct measurements_list_t) = %d", sizeof(measurements_list_t));
}


static char buffer[0x1000];

static char name[] = "MySuperSensorHello";
static char name_long[] = "MySuperSensor sueprzeio ghzuio hzergheuir ghzeuigheghzeioughuidfhguiehguiehgeuhguidfhguiezhgisdufhguisehguihiusdgh";

static const location_t loc = {
    -268435456, 268435456};

static const sensor_t sens = {
    .name = name,
    .location = loc,
};

static const measurement_t meas = {
    .time = 238723,

    .temperature = -23,
    .pressure = 132,
    .speed = 2342,

    .sensor = sens,
};

static const measurements_list_t meases = {
    .measurements = {
        meas,
        meas,
        meas,
        meas,
        meas,
    },
    .count = 5u,
};

void json_do_buf(void)
{
    int written = json_obj_encode_buf(location_descr, ARRAY_SIZE(location_descr), (const void *)&loc, buffer, sizeof(buffer));

    if (written == 0)
    {
        LOG_HEXDUMP_INF(buffer, strlen(buffer), "buffer");
    }
    else
    {
        LOG_ERR("json_arr_encode_buf error %d", written);
    }

    written = json_obj_encode_buf(sensor_descr, ARRAY_SIZE(sensor_descr), (const void *)&sens, buffer, sizeof(buffer));

    if (written == 0)
    {
        LOG_HEXDUMP_INF(buffer, strlen(buffer), "buffer");
    }
    else
    {
        LOG_ERR("json_arr_encode_buf error %d", written);
    }

    written = json_obj_encode_buf(measurement_descr, ARRAY_SIZE(measurement_descr), (const void *)&meas, buffer, sizeof(buffer));

    if (written == 0)
    {
        LOG_HEXDUMP_INF(buffer, strlen(buffer), "buffer");
    }
    else
    {
        LOG_ERR("json_arr_encode_buf error %d", written);
    }

    written = json_arr_encode_buf(measurements_list_desc, (const void *)&meases, buffer, sizeof(buffer));

    if (written == 0)
    {
        LOG_INF("size of buffer %d", strlen(buffer));

        LOG_HEXDUMP_INF(buffer, strlen(buffer), "buffer");
    }
    else
    {
        LOG_ERR("json_arr_encode_buf error %d", written);
    }
}

static uint32_t cb_counter = 0;

static int p_buffer = 0;
static size_t max_len = 0;

int json_append_bytes_cb(const char *bytes, size_t len, void *data)
{
    cb_counter++;

    if (len > max_len)
    {
        max_len = len;
    }

    if (len == 1u)
    {
        *((char*) data + p_buffer++) = *bytes;
    }
    else if (len == 0u)
    {
        return 0;
    }
    else
    {
        memcpy((char*) data + p_buffer, bytes, len);

        p_buffer += len;
    }

    return 0;
}

void json_do_cb(void){

    int written = json_arr_encode(measurements_list_desc, (const void*) &meases, json_append_bytes_cb, buffer);
    
    if (written == 0)
    {
        LOG_INF("json_append_bytes_cb called %d times max len %d", cb_counter, max_len);

        LOG_INF("written %d (p_buffer)", p_buffer);
        LOG_INF("written %d (strlen(buffer))", strlen(buffer));

        LOG_HEXDUMP_INF(buffer, strlen(buffer), "buffer");
    }
    else
    {
        LOG_ERR("json_arr_encode_buf error %d", written);
    }
}