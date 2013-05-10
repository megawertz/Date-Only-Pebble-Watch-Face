#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xE4, 0xED, 0x8F, 0xD9, 0x55, 0xF6, 0x47, 0x34, 0xA5, 0x05, 0x08, 0xA0, 0x07, 0x89, 0x85, 0xF6 }
PBL_APP_INFO(MY_UUID,
             "Big Date", "megawertz.com",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
TextLayer dateLayer;

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
	(void)t;
	(void)ctx;
	
	static char dateText[] = "Wed\nJan\n01";
	
	PblTm currentTime;
	get_time(&currentTime);
	
	// Date items in PblTm Struct if needed are int tm_mday, int tm_mon
	string_format_time(dateText, sizeof(dateText), "%a\n%b\n%d", &currentTime);
	text_layer_set_text(&dateLayer, dateText);
}

void handle_init(AppContextRef ctx) {

  	window_init(&window, "Big Date");
  	window_stack_push(&window, true /* Animated */);
  
	window_set_background_color(&window, GColorBlack);
	text_layer_init(&dateLayer, GRect(0, 0, 144 , 168 ));
  	text_layer_set_text_color(&dateLayer, GColorWhite);
  	text_layer_set_background_color(&dateLayer, GColorClear);
  	// This is the biggest default font currently in the SDK
  	text_layer_set_font(&dateLayer, fonts_get_system_font(FONT_KEY_GOTHAM_42_BOLD));
  	
  	handle_minute_tick(ctx, NULL);
	layer_add_child(&window.layer, &dateLayer.layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
    	.tick_handler = &handle_minute_tick,
    	.tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
