#include <pebble.h>

static const uint32_t START_TASK_TIMEOUT = 3000;

static Window *s_main_window;
static TextLayer *s_intro_layer;

static void main_window_load(Window *window) {
  // create TextLayer
  s_intro_layer = text_layer_create(GRect(7, 50, 90, 93));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_intro_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_intro_layer);
}

void start_task_callback(void *data) {
  // FIXME print some text to prove we were called
  text_layer_set_text(s_intro_layer, "hello\nworld!");
  text_layer_set_text_alignment(s_intro_layer, GTextAlignmentCenter);
}

static void init() {
  // setup AppTimer to callback and send message to phone
  AppTimer* timer = app_timer_register(START_TASK_TIMEOUT, (AppTimerCallback)start_task_callback, NULL);

  // create Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  // destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}