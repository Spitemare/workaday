#include <pebble.h>
#include "logging.h"
#include "enamel.h"
#include "colors.h"
#include "top-layer.h"
#include "date-layer.h"

typedef struct __attribute__((packed)) {
    DateLayer *date_layer;
} Data;

static inline uint8_t get_height(void) {
    return preferred_content_size() == PreferredContentSizeMedium ? 28 : 38;
}

static void update_proc(Layer *this, GContext *ctx) {
    log_func();
    GRect bounds = layer_get_bounds(this);
    uint8_t height = get_height();

    graphics_context_set_stroke_color(ctx, colors_get_foreground_color());
    graphics_draw_line(ctx, GPoint(0, height), GPoint(bounds.size.w, height));
    graphics_draw_line(ctx, GPoint(bounds.size.w / 2, 0), GPoint(bounds.size.w / 2, height));
}

TopLayer *top_layer_create(GRect frame) {
    log_func();
    TopLayer *this = layer_create_with_data(frame, sizeof(Data));
    layer_set_update_proc(this, update_proc);
    Data *data = layer_get_data(this);
    GRect bounds = layer_get_bounds(this);

    data->date_layer = date_layer_create(GRect(0, 0, bounds.size.w / 2 - 4, get_height()));
    layer_add_child(this, data->date_layer);

    return this;
}

void top_layer_destroy(TopLayer *this) {
    log_func();
    Data *data = layer_get_data(this);
    date_layer_destroy(data->date_layer);
    layer_destroy(this);
}