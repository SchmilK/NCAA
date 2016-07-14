#include <pebble.h>
#include <pebble-events/pebble-events.h>
#include "kiezelpay.h"
#include <main.h>
	
static Window *s_window;
static PropertyAnimation *s_beat_animation, *s_beatbox_animation, *s_badteam_animation, *s_badteambox_animation;
static Layer *s_info_layer, *s_beatbox_layer, *s_badteambox_layer, *s_health_layerWhite, *s_health_layerBlack;
static BitmapLayer *logo, *bt, *bat, *beatteam, *ftbl;
static GBitmap *s_res_logo, *s_res_clear, *s_res_bt, *s_res_bat, *s_res_batCharge, *s_res_badteam, *s_res_update,
							 *s_res_ftbl;
static TextLayer *s_time_layer, *s_date_layer, *s_date2_layer, *s_beat_layer, *s_count1_layer, *s_count2_layer, 
								 *s_step_layer, *s_td_layer;
int recon = 1, discon = 3, count = 0, runAnimation = 1, mainWindow = 0, countdown = 4,
		countdownDEFAULT = 1, countdownAni = 0, random = 0, randombad = 0, randTeam, randTeamBad, gameday, daysince, 
		daysince2, delay = 1, gametime, gamemin, gamemonth, gameapm, gameyear, height, width, steps, avgSteps, avgPct,
    sthr = 11, stmin = 0, stampm = 1, edhr = 7, edmin = 0, edampm = 0, autoRange = 20;
long startQ, endQ, currentQ;
int team = 0;
int badteam = 20;
int version = 300;
bool btHistory = true, firstTime = true, outdated = false, animationsRunning = false, timeup, premium = false,
	   healthS = false, healthTD = false, quiet = true, autoAni = true, healthSHistory = false, healthTDHistory = false,
		 healthWhite;
static int s_toggle, s_toggle2, s_toggle3;
uint8_t batteryLevel;
HealthMetric metric = HealthMetricStepCount;

//Declare animations so that they can be used before they have been defined
static void beat_animation();

//Use this as a universal destroy animation
static void destroy_property_animation(PropertyAnimation **layer_animation) {}


#ifdef PBL_PLATFORM_APLITE
#else

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "inbox_received_callback()");
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "inbox_dropped_callback()");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "outbox_failed_callback()");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "outbox_sent_callback()");
}

static bool kiezelpay_event_callback(kiezelpay_event e, void* extra_data) {
  switch (e) {
    case KIEZELPAY_ERROR:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_ERROR");
      break;
    case KIEZELPAY_BLUETOOTH_UNAVAILABLE:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_BLUETOOTH_UNAVAILABLE");
      break;
    case KIEZELPAY_INTERNET_UNAVAILABLE:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_INTERNET_UNAVAILABLE");
      break;
#if KIEZELPAY_DISABLE_TIME_TRIAL == 0
    case KIEZELPAY_TRIAL_STARTED:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_TRIAL_STARTED");
      break;
#endif
    case KIEZELPAY_TRIAL_ENDED:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_TRIAL_ENDED");
      break;
    case KIEZELPAY_CODE_AVAILABLE:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_CODE_AVAILABLE");
      break;
    case KIEZELPAY_PURCHASE_STARTED:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_PURCHASE_STARTED");
      break;
    case KIEZELPAY_LICENSED:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(): KIEZELPAY_LICENSED");
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "kiezelpay_event_callback(); unknown event");
      break;
  };
  
  //return true;   //prevent the kiezelpay lib from showing messages by signaling it that we handled the event ourselves
  return false;    //let the kiezelpay lib handle the event
}

#endif

static void info_update_proc(Layer *layer, GContext *ctx){
	GRect infoRect = GRect(0, (height / 2) + 34, width, 60);
	GRect border = GRect(-1, (height / 2) + 33, width + 2, 61);
	#ifdef PBL_RECT
		GPoint origin = GPoint(121,154);
		GPoint top = GPoint(121,139);
		GPoint right = GPoint(137,154);
	#endif
	
	graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, border, 6, GCornersTop);
	graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, infoRect, 5, GCornersTop);
	
	#ifdef PBL_RECT
		graphics_context_set_stroke_color(ctx, GColorBlack);
		graphics_draw_line(ctx, origin, top);
		graphics_draw_line(ctx, origin, right);
	#endif
}

static void beat_update_proc(Layer *layer, GContext *ctx){
	GRect beatRect = GRect(0, 0, 55, 40);
	
	graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, beatRect, 0, 0);
	graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_draw_rect(ctx, beatRect);
}

static void health_update_procWhite(Layer *layer, GContext *ctx){
	graphics_context_set_stroke_color(ctx, GColorWhite);
	for(int x = 0; x < 3; x++){
		for(int z = 0; z < 2; z++){
			GPoint leftyBig = GPoint((width / 2) - 70, (height / 2) + (-43 + x * 20 + z));
			GPoint rightyBig = GPoint((width / 2) - 59, (height / 2) + (-43 + x * 20 + z));

			graphics_draw_line(ctx, leftyBig, rightyBig);
		}
		
		for(int y = 0; y < 5; y++){
			for(int w = 0; w < 2; w++){
				GPoint lefty = GPoint((width / 2) - 67, (height / 2) + (-43 + y * 4 + x * 20 + w));
				GPoint righty = GPoint((width / 2) - 62, (height / 2) + (-43 + y * 4 + x * 20 + w));

				graphics_draw_line(ctx, lefty, righty);
			}
		}
	}
	for(int v = 0; v < 2; v++){
		GPoint leftyBigF = GPoint((width / 2) - 70, (height / 2) + (17 + v));
		GPoint rightyBigF = GPoint((width / 2) - 59, (height / 2) + (17 + v));

		graphics_draw_line(ctx, leftyBigF, rightyBigF);
	}

}

static void health_update_procBlack(Layer *layer, GContext *ctx){
	graphics_context_set_stroke_color(ctx, GColorBlack);
	for(int x = 0; x < 3; x++){
		for(int z = 0; z < 2; z++){
			GPoint leftyBig = GPoint((width / 2) - 70, (height / 2) + (-43 + x * 20 + z));
			GPoint rightyBig = GPoint((width / 2) - 59, (height / 2) + (-43 + x * 20 + z));

			graphics_draw_line(ctx, leftyBig, rightyBig);
		}
		
		for(int y = 0; y < 5; y++){
			for(int w = 0; w < 2; w++){
				GPoint lefty = GPoint((width / 2) - 67, (height / 2) + (-43 + y * 4 + x * 20 + w));
				GPoint righty = GPoint((width / 2) - 62, (height / 2) + (-43 + y * 4 + x * 20 + w));

				graphics_draw_line(ctx, lefty, righty);
			}
		}
	}
	for(int v = 0; v < 2; v++){
		GPoint leftyBigF = GPoint((width / 2) - 70, (height / 2) + (17 + v));
		GPoint rightyBigF = GPoint((width / 2) - 59, (height / 2) + (17 + v));

		graphics_draw_line(ctx, leftyBigF, rightyBigF);
	}

}

static void badteam_update_proc(Layer *layer, GContext *ctx){
	GRect badteamRect = GRect(0, 0, height+20, width);
	//GRect badteamRect = GRect(0, 0, 200, 200);
	
	#ifdef PBL_COLOR
		graphics_context_set_fill_color(ctx, (GColor)TEAM_COLORS[badteam]);
	#else
		graphics_context_set_fill_color(ctx, (GColor)AP_TEAM_COLORS[badteam]);
	#endif
  graphics_fill_rect(ctx, badteamRect, 0, 0);
}

//Function to initialize all bitmap layers
BitmapLayer* initBitmap(int x, int y, int w, int h, GBitmap *pic, Window *window){
  BitmapLayer* picLayer = bitmap_layer_create(GRect(x, y, w, h));
  bitmap_layer_set_bitmap(picLayer, pic);
  layer_add_child(window_get_root_layer(window), (Layer *)picLayer);
	bitmap_layer_set_compositing_mode(picLayer, GCompOpSet);
	bitmap_layer_set_alignment(picLayer, GAlignBottom);
  return picLayer;
}

//Function to initialize all text layers
TextLayer* initText(int x, int y, int w, int h, char* font, Window *window){
  TextLayer* textLayer = text_layer_create(GRect(x, y, w, h));
  text_layer_set_background_color(textLayer, GColorClear);
	
  text_layer_set_text_color(textLayer, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(textLayer, fonts_get_system_font(font));
  text_layer_set_text_alignment(textLayer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(textLayer));
	return textLayer;	
}

static void battery_handler(BatteryChargeState new_state) {
	uint8_t batteryLevel = new_state.charge_percent;

	//If we are charging, turn all the hearts to their charging state
	if(new_state.is_charging){
		bitmap_layer_set_bitmap(bat, s_res_batCharge);
	}
	//Otherwise we must be draining the battery
	else{
		if(batteryLevel < 30){
			bitmap_layer_set_bitmap(bat, s_res_bat);
		}
		else{
			bitmap_layer_set_bitmap(bat, s_res_clear);
		}
	}
	
	//Use this for auto animation set number
		if(batteryLevel >= autoRange){
			if(autoAni && currentQ < startQ && currentQ > endQ){
				APP_LOG(APP_LOG_LEVEL_DEBUG, "Auto: Animations ON %d", autoRange);
				runAnimation = 1;
			}
		}
		else{
			if(autoAni){
				APP_LOG(APP_LOG_LEVEL_DEBUG, "Auto: Animations OFF %d", autoRange);
				runAnimation = 0;
			}
		}
	
	layer_mark_dirty(bitmap_layer_get_layer(bat));
}

//Show current connection state
static void bt_handler(bool connected) {
	//If we are connected
  if (connected) {
		if(!btHistory){
			if(recon == 0){}
			else if(recon == 1){
				vibes_short_pulse();
			}
			else if(recon == 2){
				vibes_long_pulse();
			}
			else if(recon == 3){
				vibes_double_pulse();
			}
		}
		//Set bluetooth history to connected and show the fires
		btHistory = true;
    bitmap_layer_set_bitmap(bt, s_res_clear);
  }
	//If we aren't connected
	else {
		//And we were before
		if(btHistory){
			//Vibrate
			if(discon == 0){}
			else if(discon == 1){
				vibes_short_pulse();
			}
			else if(discon == 2){
				vibes_long_pulse();
			}
			else if(discon == 3){
				vibes_double_pulse();
			}
		}
		//Set bluetooth history to disconnected and put out the fires
    bitmap_layer_set_bitmap(bt, s_res_bt);
		btHistory = false;
  }
	
	layer_mark_dirty(bitmap_layer_get_layer(bt));
}

//Start looking for accelerometer data
static void tap_handler(AccelAxisType axis, int32_t direction) {
	if(runAnimation == 1){
		switch (axis) {
			case ACCEL_AXIS_X:
			if (direction > 0 || direction < 0) {
				if(delay == 1){
					psleep(1000);
				}
				beat_animation();
			} else {
			}
			break;

			case ACCEL_AXIS_Y:
			if (direction > 0 || direction < 0) {
				if(delay == 1){
					psleep(1000);
				}
				beat_animation();
			} else {
			}
			break;

			case ACCEL_AXIS_Z:
			if (direction > 0 || direction < 0){
				if(delay == 1){
					psleep(1000);
				}
				beat_animation();
			} else{
			}
			break;
		}
	}
}

static void health_handler(time_t starts, time_t ends, int stepper){
	HealthMetric metric = HealthMetricStepCount;
	HealthServiceAccessibilityMask mask;

	if(stepper == 0){
		// Check the metric has data available for today
		mask = health_service_metric_accessible(metric, starts, ends);
	}
	else{
		mask = health_service_metric_averaged_accessible(metric, starts, ends, HealthServiceTimeScopeDaily);
	}

	if(mask & HealthServiceAccessibilityMaskAvailable) {
		// Data is available!
		if(stepper == 0){
			static char buffer4[] = "000000";
			steps = (int)health_service_sum_today(metric);
			//steps = 88888;
			APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", steps);

			if(healthS){
				snprintf(buffer4, sizeof("000000"), "%d", steps);
				text_layer_set_text(s_step_layer, buffer4);
			}
		}
		else{
			avgSteps = (int)health_service_sum_averaged(metric, starts, ends, HealthServiceTimeScopeDaily);
			//avgSteps = 1000;
			APP_LOG(APP_LOG_LEVEL_INFO, "Average steps: %d", avgSteps);
			
			
			GRect ftblRect = {.origin = {.x = (width / 2) - 70, .y = (height / 2) + 8}, .size = {.w = 12, .h = 12}};
			
			Layer *ftblLayer_layer = bitmap_layer_get_layer(ftbl);
			avgPct = 100 * steps / avgSteps;
			if(avgPct >= 100){
				ftblRect.origin.y = ftblRect.origin.y - 64;
				//ftblRect = GRect((width / 2) - 70, (height / 2) - 56, 12, 12);

				if(healthTD){
					text_layer_set_text(s_td_layer, "T D");
				}
				else{
					text_layer_set_text(s_td_layer, "  ");
				}
			}
			else{
				ftblRect.origin.y = ftblRect.origin.y - (avgPct * 64 / 100);
				//ftblRect = GRect((width / 2) - 70, (height / 2) + 8 - (avgPct * 64 / 100), 12, 12);
				text_layer_set_text(s_td_layer, "  ");
			}

			layer_set_frame(ftblLayer_layer, ftblRect);
			layer_mark_dirty(bitmap_layer_get_layer(ftbl));
		}
	} 
	else {
		// No data recorded yet today
		APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
	}	
}

//Update the time
static void update_time() {
	
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char buffer1[] = "00:00", buffer2[] = "Jan", buffer3[] = "00";
	
	if(quiet){
		int min = tick_time->tm_min;
		int hour = tick_time->tm_hour;

		if(stampm == 1){
			if(sthr < 12){
				sthr = sthr + 12;
			}
		}
		if(stampm == 0){
			if(sthr == 12){
				sthr = 0;
			}
		}
		if(edampm == 1){
			if(edhr < 12){
				edhr = edhr + 12;
			}
		}
		if(edampm == 0){
			if(edhr == 12){
				edhr = 0;
			}
		}
		if(edampm == 2){
			if(edhr == 24){
				edhr = 0;
			}
		}
		
		startQ = sthr * 100 + stmin;
		endQ = edhr * 100 + edmin;
		currentQ = hour * 100 + min;
		
		APP_LOG(APP_LOG_LEVEL_DEBUG, "ST %d ED %d CU %d", (int)(startQ), (int)(endQ), (int)(currentQ));
		
		if(currentQ > startQ || currentQ < endQ){
			runAnimation = 0;
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Quiet Time ON");
		}
		if(currentQ < startQ && currentQ > endQ && batteryLevel >= autoRange){
			runAnimation = 1;
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Quiet Time OFF");
		}
	}

	if(countdown == 1){
		int wday = tick_time->tm_wday;
		int min = tick_time->tm_min;
		int day = tick_time->tm_mday;
		int month = tick_time->tm_mon;
		month = month + 1;
		int daylight = tick_time->tm_isdst;
		int dayyear = tick_time->tm_yday;
		int year = tick_time->tm_year;
		year = year + 1900;
		int hour;
		int countDay, countHour, countMin, countMonth;

		if(wday != 6){
			timeup = false;
		}

		if(countdownDEFAULT == 1){
			time_t rawtime;
			struct tm * ptm;
			time ( &rawtime );
			ptm = gmtime ( &rawtime );

			if(daylight == 0){
				hour = ptm->tm_hour+EST;
			}
			else{
				hour = ptm->tm_hour+EDT;
			}

			if(hour < 0){
				hour = 24 + hour;
			}

			countDay = 6 - wday;

			if(hour > 12){
				countHour = hour - 11;
				countDay--;
				countHour = 24 - countHour;
			}
			else{
				countHour = 11 - hour;
			}
			countMin = 60 - min;

			countHour = (countDay * 24) + countHour;

		}
		else{
			hour = tick_time->tm_hour;
			
			if(gameapm == 1 && gametime != 12){
				gametime = gametime + 12;
				gameapm = 0;
			}
			if(gameapm == 0 && gametime == 12){
				gametime = 0;
			}
			
			if(hour < 0){
				hour = 24 + hour;
			}

			countMonth = gamemonth - month;
			
			if(countMonth != 0){
				countDay = ((gamemonth-1) * 30);
				if(gamemonth > 1){
					countDay++;
				}
				if(gamemonth > 2){
					countDay = countDay - 2;
				}
				if(gamemonth > 3){
					countDay++;
				}
				if(gamemonth > 5){
					countDay++;
				}
				if(gamemonth > 7){
					countDay++;
				}
				if(gamemonth > 8){
					countDay++;
				}
				if(gamemonth > 10){
					countDay++;
				}
				
				countDay = countDay + gameday;

				if(gameyear - year != 0){
					countDay = countDay + (365 * (gameyear - year));
				}
				countDay = countDay - dayyear - 1;

			}
			else{
				if(gameyear - year != 0){
					countDay = (365 * (gameyear - year)) + (gameday - day);
				}
				else{
					countDay = gameday - day;
				}
			}

			//countDay = countDay + (gameday - day);

			if(hour > gametime){
				countHour = hour - (gametime - 1);
				countDay--;
				countHour = 24 - countHour;
			}
			else{
				countHour = (gametime) - hour;
			}

			countHour = (countDay * 24) + countHour;

			if(min > gamemin){
				countMin = (60 - min) + gamemin;
				countHour--;
			}
			else{
				countMin = gamemin - min;
			}
		}	

		if(countDay > 99 && !timeup){
			snprintf(buffer1, sizeof("00:00"), "99:99");
			text_layer_set_text(s_count1_layer, "Days");
			text_layer_set_text(s_count2_layer, "Hours");
		}
		else if(countHour > 99 && !timeup){
			countDay = countHour / 24;
			countHour = countHour % 24 + 1;
			if(countDay < 10 && countHour < 10){
				snprintf(buffer1, sizeof("00:00"), "0%d:0%d", countDay, countHour);
			}
			else if(countDay < 10){
				snprintf(buffer1, sizeof("00:00"), "0%d:%d", countDay, countHour);
			}
			else if(countHour < 10){
				snprintf(buffer1, sizeof("00:00"), "%d:0%d", countDay, countHour);
			}
			else{
				snprintf(buffer1, sizeof("00:00"), "%d:%d", countDay, countHour);
			}
			text_layer_set_text(s_count1_layer, "Days");
			text_layer_set_text(s_count2_layer, "Hours");
		}
		else if(!timeup){
			if(countHour < 10 && countMin < 10){
				snprintf(buffer1, sizeof("00:00"), "0%d:0%d", countHour, countMin);
			}
			else if(countHour < 10){
				snprintf(buffer1, sizeof("00:00"), "0%d:%d", countHour, countMin);
			}
			else if(countMin < 10){
				snprintf(buffer1, sizeof("00:00"), "%d:0%d", countHour, countMin);
			}
			else{
				snprintf(buffer1, sizeof("00:00"), "%d:%d", countHour, countMin);
			}
			text_layer_set_text(s_count1_layer, "Hours");
			text_layer_set_text(s_count2_layer, "Mins");

			if((countHour == 0 && countMin == 0) || countHour < 0){
				timeup = true;
			}
		}

		if(timeup){
			snprintf(buffer1, sizeof("00:00"), "00:00");
			text_layer_set_text(s_count1_layer, "Hours");
			text_layer_set_text(s_count2_layer, "Mins");
		}
	}
	else{
		// Write the current hours and minutes into the buffer
		text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
		if(clock_is_24h_style() == true) {
			//Use 24h hour format
			strftime(buffer1, sizeof("00:00"), "%H:%M", tick_time);
		} else {
			//Use 12 hour format
			strftime(buffer1, sizeof("00:00"), "%I:%M", tick_time);
		}
	}
	strftime(buffer2, sizeof("Jan"), "%b", tick_time);
	strftime(buffer3, sizeof("00"), "%e", tick_time);

	//Set the time text
	text_layer_set_text(s_time_layer, buffer1);
	text_layer_set_text(s_date_layer, buffer2);
	text_layer_set_text(s_date2_layer, buffer3);
}

//Handle when it physically chages minutes
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	// Show current time
	update_time();

	// Get the current battery level
	battery_handler(battery_state_service_peek());

	// Show current bluetooth connection state
	bt_handler(bluetooth_connection_service_peek());
	
	#ifdef PBL_HEALTH
	if(healthS || healthTD){
		health_handler(time_start_of_today(), time(NULL), 0);
		if(healthTD){
			health_handler(time_start_of_today(), time_start_of_today() + (24 * SECONDS_PER_HOUR), 1);
		}
	}
	#endif

	if(firstTime && runAnimation == 1){
		layer_set_update_proc(s_badteambox_layer, badteam_update_proc);
		bitmap_layer_set_bitmap(beatteam, s_res_badteam);
		layer_set_update_proc(s_beatbox_layer, beat_update_proc);
		text_layer_set_text(s_beat_layer, "BEAT");
		tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
		firstTime = false;
	}
	
	//beat_animation();
}

static void anim_stopped_handler(Animation *animation, bool finished, void *context) {
	// Schedule the next one, unless the app is exiting
	if (finished) {
		if(count == 0){
			count++;
			if(delay == 1){
				psleep(800);
			}
			else{
				psleep(1200);
			}
			beat_animation();
		}
		else{
			count = 0;
			if(countdownAni == 1){
				if(countdown != 4){
					countdown = 0;
				}
				text_layer_set_text(s_count1_layer, "     ");
				text_layer_set_text(s_count2_layer, "     ");
				update_time();
			}
			if(countdownAni == 2 || countdownAni == 0){
				if(countdown != 4){
					countdown = 1;
				}
				update_time();
			}
		}
	}
}

//Beat animation
static void beat_animation() {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Animate");
	if(countdownAni == 1 || countdownAni == 0){
		if(countdown != 4){
			countdown = 1;
		}
		update_time();
	}
	else if (countdownAni == 2){
		if(countdown != 4){
			countdown = 0;
		}
		text_layer_set_text(s_count1_layer, "     ");
		text_layer_set_text(s_count2_layer, "     ");
		update_time();
	}

	//We are actually using the movement of the layer
	Layer *layer = text_layer_get_layer(s_beat_layer);
	Layer *layer2 = s_beatbox_layer;
	Layer *layer3 = s_badteambox_layer;
	Layer *layer4 = bitmap_layer_get_layer(beatteam);

	//And move the created text from one spot to the other
	GRect to_rect2 = (s_toggle2) ? GRect(-(height + 20), 0, height + 20, width) : GRect(0, 0, height + 20, width);
	s_toggle2 = !s_toggle2;
	destroy_property_animation(&s_badteambox_animation);
	s_badteambox_animation = property_animation_create_layer_frame(layer3, NULL, &to_rect2);
	animation_set_duration((Animation*) s_badteambox_animation, 600);
	animation_set_curve((Animation*) s_badteambox_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_badteambox_animation, AnimationCurveEaseIn);
	animation_schedule((Animation*) s_badteambox_animation);

	GRect to_rect3 = (s_toggle3) ? GRect(-115, (height / 2) - 81, 115, 115) : GRect((width / 2) - 56, (height / 2) - 81, 115, 115);
	s_toggle3 = !s_toggle3;
	destroy_property_animation(&s_badteam_animation);
	s_badteam_animation = property_animation_create_layer_frame(layer4, NULL, &to_rect3);
	animation_set_duration((Animation*) s_badteam_animation, 650);
	animation_set_curve((Animation*) s_badteam_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_badteam_animation, AnimationCurveEaseIn);
	animation_schedule((Animation*) s_badteam_animation);

	#ifdef PBL_RECT
		GRect to_rect = (s_toggle) ? GRect(0, -40, 55, 40) : GRect(0, 0, 55, 40);
	#elif PBL_ROUND
		GRect to_rect = (s_toggle) ? GRect(63, -40, 55, 40) : GRect(63, 0, 55, 40);
	#endif
	s_toggle = !s_toggle;
	destroy_property_animation(&s_beat_animation);
	s_beat_animation = property_animation_create_layer_frame(layer, NULL, &to_rect);
	animation_set_duration((Animation*) s_beat_animation, 650);
	animation_set_curve((Animation*) s_beat_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_beat_animation, AnimationCurveEaseIn);
	animation_schedule((Animation*) s_beat_animation);

	destroy_property_animation(&s_beatbox_animation);
	s_beatbox_animation = property_animation_create_layer_frame(layer2, NULL, &to_rect);
	animation_set_duration((Animation*) s_beatbox_animation, 650);
	animation_set_curve((Animation*) s_beatbox_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_beatbox_animation, AnimationCurveEaseIn);
	animation_set_handlers((Animation*)s_beatbox_animation, (AnimationHandlers) {
		.stopped = anim_stopped_handler
	}, NULL);
	animation_schedule((Animation*) s_beatbox_animation);
}

void animationSetup(){
	Layer *window_layer = window_get_root_layer(s_window);
	s_badteambox_layer = layer_create(GRect(-(height + 20), 0, height + 20, width));
	layer_add_child(window_layer, s_badteambox_layer);
	GRect to_rect2 = GRect(-(height + 20), 0, height + 20, width);
	s_badteambox_animation = property_animation_create_layer_frame(s_badteambox_layer, NULL, &to_rect2);
	animation_schedule((Animation*) s_badteambox_animation);

	beatteam = initBitmap((width / 2) - 56, (height / 2) - 81, 115, 115, s_res_clear, s_window);
	GRect to_rect3 = GRect(-115, (height / 2) - 81, 115, 115);
	s_badteam_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(beatteam), NULL, &to_rect3);
	animation_schedule((Animation*) s_badteam_animation);

	//HERE
	#ifdef PBL_RECT
		s_beatbox_layer = layer_create(GRect(0, 0, 55, 40));
		layer_add_child(window_layer, s_beatbox_layer);
		GRect to_rect = GRect(0, -40, 55, 40);
	#elif PBL_ROUND
		s_beatbox_layer = layer_create(GRect(63, 0, 55, 40));
		layer_add_child(window_layer, s_beatbox_layer);
		GRect to_rect = GRect(63, -40, 55, 40);
	#endif
	s_beatbox_animation = property_animation_create_layer_frame(s_beatbox_layer, NULL, &to_rect);
	animation_schedule((Animation*) s_beatbox_animation);

	s_beat_layer = initText(63, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
	text_layer_set_text(s_beat_layer, "    ");
	s_beat_animation = property_animation_create_layer_frame(text_layer_get_layer(s_beat_layer), NULL, &to_rect);
	animation_schedule((Animation*) s_beat_animation);

	animationsRunning = true;
}

void setTeam(int x, int who, Layer *window_layer){
	
	if(s_res_badteam != NULL){
		gbitmap_destroy(s_res_badteam);
	}
	
	if(x == 143){
		time_t temp = time(NULL); 
		struct tm *tick_time = localtime(&temp);
		int wday = tick_time->tm_wday;
		int day = tick_time->tm_yday;
		if(who == 0){
			if(wday != 6 && random == 0){
				int oldrandTeam = randTeam;
				do {
					randTeam = rand() % 142;
				}while(oldrandTeam == randTeam && randTeam != badteam && randTeamBad != randTeam);

				persist_write_int(PER_RANDTEAM, randTeam);
				random = 1;
				persist_write_int(PER_RANDOM, random);
				daysince = day - wday;
				persist_write_int(PER_DAYSINCE, daysince);
			}
			if(wday == 0 || (day - daysince) > 6){
				APP_LOG(APP_LOG_LEVEL_DEBUG, "Reset");
				random = 0;
				daysince = 7;
				persist_write_int(PER_DAYSINCE, 7);
				persist_write_int(PER_RANDOM, random);
			}

			#ifdef PBL_COLOR
				window_set_background_color(s_window, (GColor)TEAM_COLORS[randTeam]);
			#else
				window_set_background_color(s_window, (GColor)AP_TEAM_COLORS[randTeam]);
			#endif
			
			#ifdef PBL_HEALTH
				text_layer_destroy(s_td_layer);
				text_layer_destroy(s_step_layer);
				s_step_layer = initText((width / 2) - 71, (height / 2) + 18, 110, 28, FONT_KEY_GOTHIC_14_BOLD, s_window);
				text_layer_set_text(s_step_layer, "      ");
				text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
				#ifdef PBL_RECT
					s_td_layer = initText((width / 2) - 69, (height / 2) - 84, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
				#elif PBL_ROUND
					s_td_layer = initText((width / 2) - 80, (height / 2) - 28, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
				#endif
				text_layer_set_text(s_td_layer, " ");
				#ifdef PBL_COLOR
					text_layer_set_text_color(s_td_layer, (GColor)HEALTH_COLORS[randTeam]);
					text_layer_set_text_color(s_step_layer, (GColor)HEALTH_COLORS[randTeam]);
				#else
					text_layer_set_text_color(s_td_layer, (GColor)AP_HEALTH_COLORS[randTeam]);
					text_layer_set_text_color(s_step_layer, (GColor)AP_HEALTH_COLORS[randTeam]);
				#endif
		
				#ifdef PBL_COLOR
					healthWhite = gcolor_equal((GColor)HEALTH_COLORS[randTeam], GColorWhite);
				#else
					healthWhite = gcolor_equal((GColor)AP_HEALTH_COLORS[randTeam], GColorWhite);
				#endif

				if(healthWhite && healthTD){
					layer_set_hidden(s_health_layerWhite, false);
					layer_set_hidden(s_health_layerBlack, true);
				}
				if(!healthWhite && healthTD){
					layer_set_hidden(s_health_layerBlack, false);
					layer_set_hidden(s_health_layerWhite, true);
				}
			#endif
			
			if(s_res_logo != NULL){
				gbitmap_destroy(s_res_logo);
			}
			s_res_logo = gbitmap_create_with_resource(TEAM_ICON[randTeam]);
			bitmap_layer_set_bitmap(logo, s_res_logo);
			layer_mark_dirty(bitmap_layer_get_layer(logo));
		}
		else{
			if(wday != 6 && randombad == 0){
				int oldrandTeam2 = randTeamBad;
				do {
					randTeamBad = rand() % 142;
				}while(oldrandTeam2 == randTeamBad && randTeamBad != team && randTeamBad != randTeam);

				persist_write_int(PER_RANDTEAMBAD, randTeamBad);
				randombad = 1;
				persist_write_int(PER_RANDOMBAD, randombad);
				daysince2 = day - wday;
				persist_write_int(PER_DAYSINCE2, daysince2);
			}
			if(wday == 0 || (day - daysince2) > 6){
				APP_LOG(APP_LOG_LEVEL_DEBUG, "Reset");
				randombad = 0;
				daysince2 = 7;
				persist_write_int(PER_DAYSINCE2, 7);
				persist_write_int(PER_RANDOMBAD, randombad);
			}

			#ifdef PBL_COLOR
				window_set_background_color(s_window, (GColor)TEAM_COLORS[randTeamBad]);
			#else
				window_set_background_color(s_window, (GColor)AP_TEAM_COLORS[randTeamBad]);
			#endif
			
			#ifdef PBL_HEALTH
				text_layer_destroy(s_td_layer);
				text_layer_destroy(s_step_layer);
				s_step_layer = initText((width / 2) - 71, (height / 2) + 18, 110, 28, FONT_KEY_GOTHIC_14_BOLD, s_window);
				text_layer_set_text(s_step_layer, "      ");
				text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
				#ifdef PBL_RECT
					s_td_layer = initText((width / 2) - 69, (height / 2) - 84, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
				#elif PBL_ROUND
					s_td_layer = initText((width / 2) - 80, (height / 2) - 28, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
				#endif
				text_layer_set_text(s_td_layer, " ");
				#ifdef PBL_COLOR
					text_layer_set_text_color(s_td_layer, (GColor)HEALTH_COLORS[randTeamBad]);
					text_layer_set_text_color(s_step_layer, (GColor)HEALTH_COLORS[randTeamBad]);
				#else
					text_layer_set_text_color(s_td_layer, (GColor)AP_HEALTH_COLORS[randTeamBad]);
					text_layer_set_text_color(s_step_layer, (GColor)AP_HEALTH_COLORS[randTeamBad]);
				#endif
		
				#ifdef PBL_COLOR
					healthWhite = gcolor_equal((GColor)HEALTH_COLORS[randTeamBad], GColorWhite);
				#else
					healthWhite = gcolor_equal((GColor)AP_HEALTH_COLORS[randTeamBad], GColorWhite);
				#endif

				if(healthWhite && healthTD){
					layer_set_hidden(s_health_layerWhite, false);
					layer_set_hidden(s_health_layerBlack, true);
				}
				if(!healthWhite && healthTD){
					layer_set_hidden(s_health_layerBlack, false);
					layer_set_hidden(s_health_layerWhite, true);
				}
			#endif

			if(s_res_logo != NULL){
				gbitmap_destroy(s_res_logo);
			}
			s_res_logo = gbitmap_create_with_resource(TEAM_ICON[randTeamBad]);
			bitmap_layer_set_bitmap(logo, s_res_logo);
			layer_mark_dirty(bitmap_layer_get_layer(logo));
		}

	}
	else{
		#ifdef PBL_COLOR
			window_set_background_color(s_window, (GColor)TEAM_COLORS[x]);
		#else
			window_set_background_color(s_window, (GColor)AP_TEAM_COLORS[x]);
		#endif

		if(s_res_logo != NULL){
			gbitmap_destroy(s_res_logo);
		}
		
		s_res_logo = gbitmap_create_with_resource(TEAM_ICON[x]);
		bitmap_layer_set_bitmap(logo, s_res_logo);
		layer_mark_dirty(bitmap_layer_get_layer(logo));
		
		#ifdef PBL_HEALTH
			text_layer_destroy(s_td_layer);
			text_layer_destroy(s_step_layer);
			s_step_layer = initText((width / 2) - 71, (height / 2) + 18, 110, 28, FONT_KEY_GOTHIC_14_BOLD, s_window);
			text_layer_set_text(s_step_layer, "      ");
			text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
			#ifdef PBL_RECT
				s_td_layer = initText((width / 2) - 69, (height / 2) - 84, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
			#elif PBL_ROUND
				s_td_layer = initText((width / 2) - 80, (height / 2) - 28, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
			#endif
			text_layer_set_text(s_td_layer, " ");
		
			#ifdef PBL_COLOR
				text_layer_set_text_color(s_td_layer, (GColor)HEALTH_COLORS[x]);
				text_layer_set_text_color(s_step_layer, (GColor)HEALTH_COLORS[x]);
			#else
				text_layer_set_text_color(s_td_layer, (GColor)AP_HEALTH_COLORS[x]);
				text_layer_set_text_color(s_step_layer, (GColor)AP_HEALTH_COLORS[x]);
			#endif
		
			#ifdef PBL_COLOR
				healthWhite = gcolor_equal((GColor)HEALTH_COLORS[x], GColorWhite);
			#else
				healthWhite = gcolor_equal((GColor)AP_HEALTH_COLORS[x], GColorWhite);
			#endif

			if(healthWhite && healthTD){
				layer_set_hidden(s_health_layerWhite, false);
				layer_set_hidden(s_health_layerBlack, true);
			}
			if(!healthWhite && healthTD){
				layer_set_hidden(s_health_layerBlack, false);
				layer_set_hidden(s_health_layerWhite, true);
			}
		
		#endif
	}
	
	#ifdef PBL_HEALTH
		if(healthS || healthTD){
			health_handler(time_start_of_today(), time(NULL), 0);
			if(healthTD){
				health_handler(time_start_of_today(), time_start_of_today() + (24 * SECONDS_PER_HOUR), 1);
			}
		}
	#endif
}

void setbadTeam(int x){
	if(x ==143){
		time_t temp = time(NULL); 
		struct tm *tick_time = localtime(&temp);
		int wday = tick_time->tm_wday;
		int day = tick_time->tm_yday;
		if(wday != 6 && randombad == 0){
			int oldrandTeam2 = randTeamBad;
			do {
				randTeamBad = rand() % 142;
			}while(oldrandTeam2 == randTeamBad && randTeamBad != team && randTeamBad != randTeam);

			persist_write_int(PER_RANDTEAMBAD, randTeamBad);
			randombad = 1;
			persist_write_int(PER_RANDOMBAD, randombad);
			daysince2 = day - wday;
			persist_write_int(PER_DAYSINCE2, daysince2);
		}
		if(wday == 0 || (day - daysince2) > 6){
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Reset");
			randombad = 0;
			daysince2 = 7;
			persist_write_int(PER_DAYSINCE2, 7);
			persist_write_int(PER_RANDOMBAD, randombad);
		}
		if(s_res_badteam != NULL){
			//gbitmap_destroy(s_res_badteam);
		}
		s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[randTeamBad]);
		bitmap_layer_set_bitmap(beatteam, s_res_badteam);
		layer_mark_dirty(bitmap_layer_get_layer(beatteam));

	}
	else{
		if(s_res_badteam != NULL){
			//gbitmap_destroy(s_res_badteam);
		}
		s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[x]);
		bitmap_layer_set_bitmap(beatteam, s_res_badteam);
		layer_mark_dirty(bitmap_layer_get_layer(beatteam));
	}
}

//Process the data coming from the configruable
void process_tuple(Tuple *t){	
  int key = t->key;
  int value = t->value->int32;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Got key %d, value %d", key, value);
	//Switch from set value to set value from configruable
  switch(key){
		//Animations 0 on, 1 off, 2 auto
		case KEY_ANIMATION:
		if(value == 0){
			persist_write_int(PER_ANIMATION, 1);
			persist_write_bool(PER_AUTOANIMATION, false);
			runAnimation = 1;
			autoAni = false;
		}
		else if(value == 1){
			persist_write_int(PER_ANIMATION, 0);
			persist_write_bool(PER_AUTOANIMATION, false);
			runAnimation = 0;
			autoAni = false;
		}
		else if(value ==2){
			persist_write_int(PER_ANIMATION, 1);
			persist_write_bool(PER_AUTOANIMATION, true);
			runAnimation = 1;
			autoAni = true;
		}
		break;
		//Auto Animation range
		case KEY_AUTORANGE:
		autoRange = value;
		persist_write_int(PER_AUTORANGE, value);
		break;
		//Bluetooth disconnect vibrations
		case KEY_DISCONNECT:
		if(value == 0){
			persist_write_int(PER_DISCONNECT, 0);
			discon = 0;
		}
		else if(value == 1){
			persist_write_int(PER_DISCONNECT, 1);
			discon = 1;
		}
		else if(value == 2){
			persist_write_int(PER_DISCONNECT, 2);
			discon = 2;
		}
		else if(value == 3){
			persist_write_int(PER_DISCONNECT, 3);
			discon = 3;
		}
		break;
		//Bluetooth reconnect vibrations
		case KEY_RECONNECT:
		if(value == 0){
			persist_write_int(PER_RECONNECT, 0);
			recon = 0;
		}
		else if(value == 1){
			persist_write_int(PER_RECONNECT, 1);
			recon = 1;
		}
		else if(value == 2){
			persist_write_int(PER_RECONNECT, 2);
			recon = 2;
		}
		else if(value == 3){
			persist_write_int(PER_RECONNECT, 3);
			recon = 3;
		}
		break;
		//Check version
		case KEY_VERSION:
		if(value != version && !outdated){
			
			#ifdef PBL_COLOR
				s_res_update = gbitmap_create_with_resource(RESOURCE_ID_update);
			#else
				
			#endif
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Outdated");
			outdated = true;
			bitmap_layer_set_bitmap(logo, s_res_update);
			layer_mark_dirty(bitmap_layer_get_layer(logo));
		}
		break;
		case KEY_TEAM:
		team = value;
		if(team == 143){
			premium = true;
		}
		persist_write_int(PER_TEAM, team);
		break;
		case KEY_BADTEAM:
		badteam = value;
		if(team == 143){
			premium = true;
		}
		persist_write_int(PER_BADTEAM, badteam);
		break;
		case KEY_WINDOW:
		mainWindow = value;
		persist_write_int(PER_WINDOW, mainWindow);
		break;
		case KEY_COUNTDOWN:
		if(value == 0){
			countdown = 4;
			persist_write_int(PER_COUNTDOWN, 4);
			text_layer_set_text(s_count1_layer, "     ");
			text_layer_set_text(s_count2_layer, "     ");
		}
		else{
			premium = true;
			if(countdownAni == 0 || countdownAni == 2){
				countdown = 1;
				persist_write_int(PER_COUNTDOWN, 1);
			}
			else{
				countdown = 0;
				persist_write_int(PER_COUNTDOWN, 0);
			}
		}
		break;
		case KEY_COUNTDOWNDEFAULT:
		countdownDEFAULT = value;
		persist_write_int(PER_COUNTDOWNDEFAULT, countdownDEFAULT);
		break;
		case KEY_COUNTDOWNANI:
		if(value == 0){
			countdownAni = 0;
			persist_write_int(PER_COUNTDOWNANI, 0);
		}
		else if(value == 1){
			countdownAni = 1;
			if(countdown != 4){
				countdown = 0;				
				persist_write_int(PER_COUNTDOWN, 0);
			}
			persist_write_int(PER_COUNTDOWNANI, 1);
			text_layer_set_text(s_count1_layer, "     ");
			text_layer_set_text(s_count2_layer, "     ");
		}
		else{
			countdownAni = 2;
			if(countdown != 4){
				countdown = 1;
				persist_write_int(PER_COUNTDOWN, 1);
			}
			persist_write_int(PER_COUNTDOWNANI, 2);
		}
		break;
		case KEY_GAMEDAY:
		gameday = value;
		persist_write_int(PER_GAMEDAY, gameday);
		break;
		case KEY_DELAY:
		delay = value;
		persist_write_int(PER_DELAY, delay);
		break;
		case KEY_GAMETIME:
		gametime = value;
		persist_write_int(PER_GAMETIME, gametime);
		break;
		case KEY_GAMEMIN:
		gamemin = value;
		persist_write_int(PER_GAMEMIN, gamemin);
		break;
		case KEY_GAMEMONTH:
		gamemonth = value;
		persist_write_int(PER_GAMEMONTH, gamemonth);
		break;
		case KEY_GAMEAPM:
		gameapm = value;
		persist_write_int(PER_GAMEAPM, gameapm);
		break;
		case KEY_GAMEYEAR:
		gameyear = value;
		persist_write_int(PER_GAMEYEAR, gameyear);
		break;
		case KEY_QUIET:
		if(value == 0){
			quiet = true;
			persist_write_bool(PER_QUIET, true);
		}
		else{
			quiet = false;
			persist_write_bool(PER_QUIET, false);
		}
		break;
		case KEY_STHR:
		sthr = value;
		persist_write_int(PER_STHR, value);
		break;
		case KEY_STMIN:
		stmin = value;
		persist_write_int(PER_STMIN, value);
		break;
		case KEY_STAMPM:
		stampm = value;
		persist_write_int(PER_STAMPM, value);
		break;
		case KEY_EDHR:
		edhr = value;
		persist_write_int(PER_EDHR, value);
		break;
		case KEY_EDMIN:
		edmin = value;
		persist_write_int(PER_EDMIN, value);
		break;
		case KEY_EDAMPM:
		edampm = value;
		persist_write_int(PER_EDAMPM, value);
		break;
		//Health stuff
		case KEY_STEPS:
		if(value == 0){
			persist_write_bool(PER_STEPS, false);
			healthS = false;
			if(healthSHistory){
				text_layer_set_text(s_step_layer, "      ");
				healthSHistory = false;
			}
		}
		else if(value == 1){
			persist_write_bool(PER_STEPS, true);
			healthS = true;
			premium = true;
			if(!healthSHistory){
				health_handler(time_start_of_today(), time(NULL), 0);
				healthSHistory = true;
			}
		}
		break;
		case KEY_TD:
		if(value == 0){
			persist_write_bool(PER_TD, false);
			healthTD = false;
			if(healthTDHistory){
				bitmap_layer_set_bitmap(ftbl, s_res_clear);
				layer_mark_dirty(bitmap_layer_get_layer(ftbl));
				layer_set_hidden(s_health_layerWhite, true);
				layer_set_hidden(s_health_layerBlack, true);
				healthTDHistory = false;
			}
		}
		else if(value == 1){
			persist_write_bool(PER_TD, true);
			healthTD = true;
			premium = true;
			if(!healthTDHistory){
				bitmap_layer_set_bitmap(ftbl, s_res_ftbl);
				layer_mark_dirty(bitmap_layer_get_layer(ftbl));
				healthTDHistory = true;
			}
		}
		break;
	}
	
}

//Look through all of the configurable data
void inbox(DictionaryIterator *iter, void *context){
	Layer *window_layer = window_get_root_layer(s_window);
	Tuple *t = dict_read_first(iter);
	if(t == NULL){
		APP_LOG(APP_LOG_LEVEL_DEBUG, "FLOP");
	}
  if(t){
		APP_LOG(APP_LOG_LEVEL_INFO, "Processing");
    process_tuple(t);
  }
  while(t != NULL){
		APP_LOG(APP_LOG_LEVEL_INFO, "Looking");
    t = dict_read_next(iter);
    if(t){
      process_tuple(t);
    }
  }
	
	if(premium == true){
		#ifdef PBL_PLATFORM_APLITE
		#else
			kiezelpay_start_purchase();
		#endif
		int32_t result = kiezelpay_get_status();
		bool paid = true;
		if(result & KIEZELPAY_LICENSED){
			paid = true;
		APP_LOG(APP_LOG_LEVEL_INFO, "Paid");
		}
		else{
			//paid = false;
		APP_LOG(APP_LOG_LEVEL_INFO, "Not Paid");
		}
		if(!paid){
			countdown = 4;
			persist_write_int(PER_COUNTDOWN, 4);
			badteam = 20;
			persist_write_int(PER_BADTEAM, badteam);
			team = 0;
			persist_write_int(PER_TEAM, team);
			persist_write_bool(PER_TD, false);
			healthTD = false;
			if(healthTDHistory){
				bitmap_layer_set_bitmap(ftbl, s_res_clear);
				layer_mark_dirty(bitmap_layer_get_layer(ftbl));
				layer_set_hidden(s_health_layerWhite, true);
				layer_set_hidden(s_health_layerBlack, true);
				healthTDHistory = false;
			}
			persist_write_bool(PER_STEPS, false);
			healthS = false;
			if(healthSHistory){
				text_layer_set_text(s_step_layer, "      ");
				healthSHistory = false;
			}
		}
	}
	
	if(mainWindow == 0){
		if(s_beat_layer != NULL){
			text_layer_destroy(s_beat_layer);
			layer_destroy(s_beatbox_layer);
		}
		
		if(!outdated){
			setTeam(team, 0, window_layer);
		}

		if(runAnimation == 1){
			if(!animationsRunning){
				animationSetup();
			}
			else{
				//HERE
				#ifdef PBL_RECT
					s_beatbox_layer = layer_create(GRect(0, 0, 55, 40));
				#elif PBL_ROUND
					s_beatbox_layer = layer_create(GRect(63, 0, 55, 40));
				#endif
				layer_set_update_proc(s_beatbox_layer, beat_update_proc);
				layer_add_child(window_layer, s_beatbox_layer);
				#ifdef PBL_RECT
					GRect to_rect = GRect(0, -40, 55, 40);
				#elif PBL_ROUND
					GRect to_rect = GRect(63, -40, 55, 40);
				#endif
				s_beatbox_animation = property_animation_create_layer_frame(s_beatbox_layer, NULL, &to_rect);
				animation_schedule((Animation*) s_beatbox_animation);

				#ifdef PBL_RECT
					s_beat_layer = initText(0, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
				#elif PBL_ROUND
					s_beat_layer = initText(63, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
				#endif
				text_layer_set_text(s_beat_layer, "BEAT");
				s_beat_animation = property_animation_create_layer_frame(text_layer_get_layer(s_beat_layer), NULL, &to_rect);
				animation_schedule((Animation*) s_beat_animation);
			}
			setbadTeam(badteam);
		}
	}
	else{
		if(!outdated){
			setTeam(badteam, 1, window_layer);
		}
		//HERE
		runAnimation = 0;
		#ifdef PBL_RECT
			s_beatbox_layer = layer_create(GRect(0, 0, 55, 40));
		#elif PBL_ROUND
			s_beatbox_layer = layer_create(GRect(63, 0, 55, 40));
		#endif
		layer_set_update_proc(s_beatbox_layer, beat_update_proc);
		layer_add_child(window_layer, s_beatbox_layer);
		#ifdef PBL_RECT
			s_beat_layer = initText(0, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
		#elif PBL_ROUND
			s_beat_layer = initText(63, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
		#endif
		text_layer_set_text(s_beat_layer, "BEAT");
	}

	
	update_time();
	
}

static void main_window_load(Window *window) {
	
	Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
	GRect layer_bounds = window_bounds;

	height = layer_bounds.size.h;
	width = layer_bounds.size.w;
	
	s_res_clear = NULL;
	
	#ifdef PBL_HEALTH	
		s_health_layerWhite = layer_create(GRect(0, 0, width/5, height*2/3));
		layer_add_child(window_layer, s_health_layerWhite);
		layer_set_update_proc(s_health_layerWhite, health_update_procWhite);
		layer_set_hidden(s_health_layerWhite, true);

		s_health_layerBlack = layer_create(GRect(0, 0, width/5, height*2/3));
		layer_add_child(window_layer, s_health_layerBlack);
		layer_set_update_proc(s_health_layerBlack, health_update_procBlack);
		layer_set_hidden(s_health_layerBlack, true);
	#endif
	
	logo = initBitmap((width / 2) - 56, (height / 2) - 81, 115, 115, s_res_clear, s_window);
	
	
	#ifdef PBL_HEALTH
		s_res_ftbl = gbitmap_create_with_resource(RESOURCE_ID_ftbl);
		ftbl = initBitmap((width / 2) - 70, (height / 2) + 8, 12, 12, s_res_clear, s_window);
		if(healthS){
			healthSHistory = true;
		}
		if(healthTD){
			bitmap_layer_set_bitmap(ftbl, s_res_ftbl);
			layer_mark_dirty(bitmap_layer_get_layer(ftbl));
		}
	#endif
	
	if(mainWindow == 0){
		setTeam(team, 0, window_layer);
	}
	else{
		setTeam(badteam, 1, window_layer);
		#ifdef PBL_RECT
			s_beatbox_layer = layer_create(GRect(0, 0, 55, 40));
		#elif PBL_ROUND
			s_beatbox_layer = layer_create(GRect(63, 0, 55, 40));
		#endif
		layer_set_update_proc(s_beatbox_layer, beat_update_proc);
		layer_add_child(window_layer, s_beatbox_layer);
		
		#ifdef PBL_RECT
			s_beat_layer = initText(0, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
		#elif PBL_ROUND
			s_beat_layer = initText(63, 0, 55, 40, FONT_KEY_GOTHIC_28_BOLD, s_window);
		#endif
		text_layer_set_text(s_beat_layer, "BEAT");
		runAnimation = 0;
	}
	
	s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[badteam]);
	
	if(runAnimation == 1){		
		animationSetup();
	}
				
	// Create Layer that the path will be drawn on
  s_info_layer = layer_create(GRect(0, 0, width, height));
  layer_set_update_proc(s_info_layer, info_update_proc);
  layer_add_child(window_layer, s_info_layer);
	
	#ifdef PBL_RECT
		s_time_layer = initText(0, 115, 120, 50, FONT_KEY_LECO_42_NUMBERS, s_window);
		text_layer_set_text(s_time_layer, "20:00");
		s_date_layer = initText(107, 120, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_date_layer, "Jan");
		s_date2_layer = initText(110, 135, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_date_layer, "00");
		s_count1_layer = initText(15, 153, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_count1_layer, "     ");
		s_count2_layer = initText(65, 153, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_count2_layer, "     ");
	#elif PBL_ROUND
		s_time_layer = initText(30, 115, 120, 50, FONT_KEY_LECO_42_NUMBERS, s_window);
		text_layer_set_text(s_time_layer, "20:00");
		s_date_layer = initText(133, 122, 45, 25, FONT_KEY_GOTHIC_14, s_window);
		text_layer_set_text(s_date_layer, "Jan");
		s_date2_layer = initText(131, 133, 45, 25, FONT_KEY_GOTHIC_14, s_window);
		text_layer_set_text(s_date_layer, "00");
		s_count1_layer = initText(45, 153, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_count1_layer, "     ");
		s_count2_layer = initText(90, 153, 45, 25, FONT_KEY_GOTHIC_14_BOLD, s_window);
		text_layer_set_text(s_count2_layer, "     ");
	#endif
	
	s_res_bt = gbitmap_create_with_resource(RESOURCE_ID_bt);
	s_res_bat = gbitmap_create_with_resource(RESOURCE_ID_bat);
	s_res_batCharge = gbitmap_create_with_resource(RESOURCE_ID_batCharge);
	
	#ifdef PBL_RECT
		bt = initBitmap(122, 157, 6, 7, s_res_clear, s_window);
		bat = initBitmap(132, 157, 4, 7, s_res_clear, s_window);
	#elif PBL_ROUND
		bt = initBitmap(26, 129, 6, 7, s_res_clear, s_window);
		bat = initBitmap(28, 139, 4, 7, s_res_clear, s_window);
	#endif
	
	// Make sure the time is displayed from the start
  update_time();
	
	// Get the current battery level
	battery_handler(battery_state_service_peek());
	
	// Show current bluetooth connection state
  bt_handler(bluetooth_connection_service_peek());
	
	#ifdef PBL_HEALTH
	if(healthS || healthTD){
		health_handler(time_start_of_today(), time(NULL), 0);
		if(healthTD){
			health_handler(time_start_of_today(), time_start_of_today() + (24 * SECONDS_PER_HOUR), 1);
		}
	}
	#endif
}

static void main_window_unload(Window *window) {
	// Destroy all layers
	bitmap_layer_destroy(logo);
	bitmap_layer_destroy(bt);
	bitmap_layer_destroy(bat);
	
	gbitmap_destroy(s_res_logo);
	gbitmap_destroy(s_res_bt);
	gbitmap_destroy(s_res_bat);
	gbitmap_destroy(s_res_batCharge);
	if(s_res_badteam != NULL){
		gbitmap_destroy(s_res_badteam);
	}
	gbitmap_destroy(s_res_clear);
	
	#ifdef PBL_HEALTH
		if(s_res_ftbl != NULL){
			gbitmap_destroy(s_res_ftbl);
		}
		bitmap_layer_destroy(ftbl);
		text_layer_destroy(s_td_layer);
		text_layer_destroy(s_step_layer);
		layer_destroy(s_health_layerBlack);
		layer_destroy(s_health_layerWhite);
	#endif
	
	text_layer_destroy(s_time_layer);
	text_layer_destroy(s_date_layer);
	text_layer_destroy(s_date2_layer);
	text_layer_destroy(s_count1_layer);
	text_layer_destroy(s_count2_layer);
		
	layer_destroy(s_info_layer);
	
	destroy_property_animation(&s_beat_animation);
	
	if(animationsRunning){
		bitmap_layer_destroy(beatteam);
		text_layer_destroy(s_beat_layer);
		layer_destroy(s_beatbox_layer);
		layer_destroy(s_badteambox_layer);
	}
	
	if(mainWindow == 1 && !animationsRunning){
		text_layer_destroy(s_beat_layer);
		layer_destroy(s_beatbox_layer);
	}
	
	if(outdated){
		gbitmap_destroy(s_res_update);
	}
}

static void init() {
  // Create main Window element and assign to pointer
  s_window = window_create();
		
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
	
		//Load any persistant data from before watch close
	if(persist_exists(PER_ANIMATION)){
		runAnimation = persist_read_int(PER_ANIMATION);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 1: %d", runAnimation);
	}
	if(persist_exists(PER_DISCONNECT)){
		discon = persist_read_int(PER_DISCONNECT);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 2: %d", discon);
	}
	if(persist_exists(PER_RECONNECT)){
		recon = persist_read_int(PER_RECONNECT);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 3: %d", recon);
	}
	if(persist_exists(PER_TEAM)){
		team = persist_read_int(PER_TEAM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 4: %d", team);
	}
	if(persist_exists(PER_BADTEAM)){
		badteam = persist_read_int(PER_BADTEAM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 5: %d", badteam);
	}
	if(persist_exists(PER_WINDOW)){
		mainWindow = persist_read_int(PER_WINDOW);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 6: %d", mainWindow);
	}
	if(persist_exists(PER_COUNTDOWN)){
		countdown = persist_read_int(PER_COUNTDOWN);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 7: %d", countdown);
	}
	if(persist_exists(PER_COUNTDOWNDEFAULT)){
		countdownDEFAULT = persist_read_int(PER_COUNTDOWNDEFAULT);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 8: %d", countdownDEFAULT);
	}
	if(persist_exists(PER_COUNTDOWNANI)){
		countdownAni = persist_read_int(PER_COUNTDOWNANI);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 9: %d", countdownAni);
	}
	if(persist_exists(PER_RANDOM)){
		random = persist_read_int(PER_RANDOM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 10: %d", random);
	}
	if(persist_exists(PER_RANDTEAM)){
		randTeam = persist_read_int(PER_RANDTEAM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 11: %d", randTeam);
	}
	if(persist_exists(PER_GAMEDAY)){
		gameday = persist_read_int(PER_GAMEDAY);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 12: %d", gameday);
	}
	if(persist_exists(PER_DAYSINCE)){
		daysince = persist_read_int(PER_DAYSINCE);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 13: %d", daysince);
	}
	if(persist_exists(PER_DELAY)){
		delay = persist_read_int(PER_DELAY);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 14: %d", delay);
	}
	if(persist_exists(PER_GAMETIME)){
		gametime = persist_read_int(PER_GAMETIME);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 15: %d", gametime);
	}
	if(persist_exists(PER_GAMEMIN)){
		gamemin = persist_read_int(PER_GAMEMIN);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 16: %d", gamemin);
	}
	if(persist_exists(PER_GAMEMONTH)){
		gamemonth = persist_read_int(PER_GAMEMONTH);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 17: %d", gamemonth);
	}
	if(persist_exists(PER_GAMEAPM)){
		gameapm = persist_read_int(PER_GAMEAPM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 18: %d", gameapm);
	}
	if(persist_exists(PER_GAMEYEAR)){
		gameyear = persist_read_int(PER_GAMEYEAR);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 19: %d", gameyear);
	}
	if(persist_exists(PER_RANDOMBAD)){
		randombad = persist_read_int(PER_RANDOMBAD);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 20: %d", randombad);
	}
	if(persist_exists(PER_RANDTEAMBAD)){
		randTeamBad = persist_read_int(PER_RANDTEAMBAD);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 21: %d", randTeamBad);
	}
	if(persist_exists(PER_DAYSINCE2)){
		daysince2 = persist_read_int(PER_DAYSINCE2);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 22: %d", daysince2);
	}
	if(persist_exists(PER_QUIET)){
		quiet = persist_read_bool(PER_QUIET);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 23: %d", quiet);
	}
	if(persist_exists(PER_STHR)){
		sthr = persist_read_int(PER_STHR);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 24: %d", sthr);
	}
	if(persist_exists(PER_STMIN)){
		stmin = persist_read_int(PER_STMIN);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 25: %d", stmin);
	}
	if(persist_exists(PER_STAMPM)){
		stampm = persist_read_int(PER_STAMPM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 26: %d", stampm);
	}
	if(persist_exists(PER_EDHR)){
		edhr = persist_read_int(PER_EDHR);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 27: %d", edhr);
	}
	if(persist_exists(PER_EDMIN)){
		edmin = persist_read_int(PER_EDMIN);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 28: %d", edmin);
	}
	if(persist_exists(PER_EDAMPM)){
		edampm = persist_read_int(PER_EDAMPM);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 29: %d", edampm);
	}
	if(persist_exists(PER_AUTORANGE)){
		autoRange = persist_read_int(PER_AUTORANGE);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 30: %d", autoRange);
	}	
	if(persist_exists(PER_AUTOANIMATION)){
		autoAni = persist_read_bool(PER_AUTOANIMATION);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 31: %d", autoAni);
	}
	if(persist_exists(PER_STEPS)){
		healthS = persist_read_bool(PER_STEPS);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 32: %d", healthS);
	}	
	if(persist_exists(PER_TD)){
		healthTD = persist_read_bool(PER_TD);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 33: %d", healthTD);
	}

	// Show the Window on the watch, with animated=true
  window_stack_push(s_window, true);
	
	// Subscribe to the Battery State Service
  battery_state_service_subscribe(battery_handler);
	
	// Subscribe to Bluetooth updates
  bluetooth_connection_service_subscribe(bt_handler);
	
	// Subsribe to Accelorator services
	accel_tap_service_subscribe(tap_handler);
	
	if(firstTime && runAnimation == 1){
		// Register with TickTimerService as seconds initially
		tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Seconds Set");
	}
	else{
		//This is here for the just in case
		tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Minutes Set");
	}
	
	// Subscribe to js data
	app_message_register_inbox_received(inbox);
  app_message_open(200, 32);//app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	#ifdef PBL_PLATFORM_APLITE
	#else
  // Listen for KiezelPay events
  kiezelpay_set_event_handler(kiezelpay_event_callback);

  // Initiate KiezelPay
  kiezelpay_init();
  
  // The pebble-events package is used for appmessages, check https://www.npmjs.com/package/pebble-events on how to receive your own appmessages as well
  events_app_message_open();

	// Configure your own AppMessage settings for the pebble-events package if you also need app messages
	events_app_message_register_inbox_received(inbox_received_callback, NULL);
	events_app_message_register_inbox_dropped(inbox_dropped_callback, NULL);
	events_app_message_register_outbox_sent(outbox_sent_callback, NULL);
	events_app_message_register_outbox_failed(outbox_failed_callback, NULL);
	#endif
	
}

static void deinit() {
	//Stop any animations that are going
	animation_unschedule_all();
	//Turn off accelorator services
	accel_tap_service_unsubscribe();
	//Turn off battery peek
	battery_state_service_unsubscribe();
	//Turn off bluetooth peek
	bluetooth_connection_service_unsubscribe();
	//Turn off time peek
	tick_timer_service_unsubscribe();
	//Turn off KiezelPay
	#ifdef PBL_PLATFORM_APLITE
	#else
	kiezelpay_deinit();
	#endif
	// Destroy Window
  window_destroy(s_window);
}

int main(void) {
  init();
	app_event_loop();
	deinit();
}