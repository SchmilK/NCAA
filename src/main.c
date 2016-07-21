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
    sthr = 11, stmin = 0, stampm = 1, edhr = 7, edmin = 0, edampm = 0, autoRange = 20, startQ, endQ, currentQ, 
		windowHist = 0;
int team = 0;
int badteam = 20;
int version = 300;
bool debug = false;
bool btHistory = true, firstTime = true, outdated = false, animationsRunning = false, timeup, premium = false,
	   healthS = false, healthTD = false, quiet = false, autoAni = true, healthSHistory = false, healthTDHistory = false,
		 healthWhite, paid = false, runAniHist = true;
static int s_toggle, s_toggle2, s_toggle3;
uint8_t batteryLevel;
HealthMetric metric = HealthMetricStepCount;

//Declare animations so that they can be used before they have been defined
static void beat_animation();

//Use this as a universal destroy animation
static void destroy_property_animation(PropertyAnimation **layer_animation) {}

#ifdef PBL_PLATFORM_APLITE
#else
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
	GRect beatRect = GRect(0, 0, 55, 32);
	
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
	int bgTeam;
	
	if(mainWindow == 0){
		bgTeam = badteam;
	}
	else{
		bgTeam = team;
	}
	#ifdef PBL_COLOR
		graphics_context_set_fill_color(ctx, (GColor)TEAM_COLORS[bgTeam]);
	#else
		graphics_context_set_fill_color(ctx, (GColor)AP_TEAM_COLORS[bgTeam]);
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
				if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Auto: Animations ON %d", autoRange);}
				runAnimation = 1;
			}
		}
		else{
			if(autoAni){
				if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Auto: Animations OFF %d", autoRange);}
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
			if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", steps);}

			if(healthS){
				snprintf(buffer4, sizeof("000000"), "%d", steps);
				text_layer_set_text(s_step_layer, buffer4);
			}
		}
		else{
			avgSteps = (int)health_service_sum_averaged(metric, starts, ends, HealthServiceTimeScopeDaily);
			//avgSteps = 1000;
			if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Average steps: %d", avgSteps);}
			
			
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

		currentQ = hour * 100 + min;
		
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "ST %d ED %d CU %d", (int)(startQ), (int)(endQ), (int)(currentQ));}
		
		if(currentQ > startQ || currentQ < endQ){
			runAnimation = 0;
			if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Quiet Time ON");}
		}
		if(currentQ < startQ && currentQ > endQ && batteryLevel >= autoRange){
			runAnimation = 1;
			if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Quiet Time OFF");}
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
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Minutes Set");
		firstTime = false;
	}
	else if (firstTime && runAnimation == 0){
		//Make sure at least minutes are set
		tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Minutes Set");
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
	if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Animate");}
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
	//GRect to_rect2 = (s_toggle2) ? GRect(-(width + 20), 0, width + 20, height) : GRect(0, 0, width + 20, height);
	GRect to_rect2 = (s_toggle2) ? GRect(-width, 0, width, height) : GRect(0, 0, width, height);
	s_toggle2 = !s_toggle2;
	destroy_property_animation(&s_badteambox_animation);
	s_badteambox_animation = property_animation_create_layer_frame(layer3, NULL, &to_rect2);
	animation_set_duration((Animation*) s_badteambox_animation, 650);
	animation_set_curve((Animation*) s_badteambox_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_badteambox_animation, AnimationCurveEaseIn);
	animation_schedule((Animation*) s_badteambox_animation);

	int beforeAni, afterAni;
	if(mainWindow == 0){
		beforeAni = -35;
		afterAni = 0;
	}
	else{
		beforeAni = 0;
		afterAni = -35;
	}
	#ifdef PBL_RECT
		GRect to_rect = (s_toggle) ? GRect(0, beforeAni, 55, 32) : GRect(0, afterAni, 55, 32);
	#elif PBL_ROUND
		GRect to_rect = (s_toggle) ? GRect(63, beforeAni, 55, 32) : GRect(63, afterAni, 55, 32);
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
	animation_schedule((Animation*) s_beatbox_animation);


	GRect to_rect3 = (s_toggle3) ? GRect(-115, (height / 2) - 81, 115, 115) : GRect((width / 2) - 56, (height / 2) - 81, 115, 115);
	s_toggle3 = !s_toggle3;
	destroy_property_animation(&s_badteam_animation);
	s_badteam_animation = property_animation_create_layer_frame(layer4, NULL, &to_rect3);
	animation_set_duration((Animation*) s_badteam_animation, 650);
	animation_set_curve((Animation*) s_badteam_animation, AnimationCurveEaseOut);
	animation_set_curve((Animation*) s_badteam_animation, AnimationCurveEaseIn);
	animation_set_handlers((Animation*)s_badteam_animation, (AnimationHandlers) {
			.stopped = anim_stopped_handler
		}, NULL);
	animation_schedule((Animation*) s_badteam_animation);

}

void animationSetup(){
	Layer *window_layer = window_get_root_layer(s_window);
	s_badteambox_layer = layer_create(GRect(-(width + 20), 0, width + 20, height));
	layer_add_child(window_layer, s_badteambox_layer);
	GRect to_rect2 = GRect(-(width + 20), 0, width + 20, height);
	s_badteambox_animation = property_animation_create_layer_frame(s_badteambox_layer, NULL, &to_rect2);
	animation_schedule((Animation*) s_badteambox_animation);

	beatteam = initBitmap((width / 2) - 56, (height / 2) - 81, 115, 115, s_res_clear, s_window);
	GRect to_rect3 = GRect(-115, (height / 2) - 81, 115, 115);
	s_badteam_animation = property_animation_create_layer_frame(bitmap_layer_get_layer(beatteam), NULL, &to_rect3);
	animation_schedule((Animation*) s_badteam_animation);

	int beforeAni, afterAni;
	if(mainWindow == 0){
		beforeAni = -35;
		afterAni = 0;
	}
	else{
		beforeAni = 0;
		afterAni = -35;
	}

	#ifdef PBL_RECT
		s_beatbox_layer = layer_create(GRect(0, afterAni, 55, 32));
		layer_add_child(window_layer, s_beatbox_layer);
		GRect to_rect = GRect(0, beforeAni, 55, 32);
	#elif PBL_ROUND
		s_beatbox_layer = layer_create(GRect(63, afterAni, 55, 32));
		layer_add_child(window_layer, s_beatbox_layer);
		GRect to_rect = GRect(63, beforeAni, 55, 32);
	#endif
	s_beatbox_animation = property_animation_create_layer_frame(s_beatbox_layer, NULL, &to_rect);
	animation_schedule((Animation*) s_beatbox_animation);

	s_beat_layer = initText(63, afterAni, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
  text_layer_set_text_alignment(s_beat_layer, GTextAlignmentCenter);
	text_layer_set_text(s_beat_layer, "    ");
	s_beat_animation = property_animation_create_layer_frame(text_layer_get_layer(s_beat_layer), NULL, &to_rect);
	animation_schedule((Animation*) s_beat_animation);


	animationsRunning = true;
}

void setTeam(int x, int who, Layer *window_layer){
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
				if(s_td_layer != NULL){
						text_layer_destroy(s_td_layer);
				}
				if(s_step_layer != NULL){
						text_layer_destroy(s_step_layer);
				}
				s_step_layer = initText((width / 2) - 71, (height / 2) + 18, 110, 28, FONT_KEY_GOTHIC_14_BOLD, s_window);
				text_layer_set_text(s_step_layer, "      ");
				text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
				#ifdef PBL_RECT
					s_td_layer = initText((width / 2) - 57, (height / 2) - 9, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
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
					s_td_layer = initText((width / 2) - 57, (height / 2) - 9, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
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

		#ifdef PBL_HEALTH
			if(s_td_layer != NULL){
				text_layer_destroy(s_td_layer);
			}
			if(s_step_layer != NULL){
				text_layer_destroy(s_step_layer);
			}
		#endif
		
		if(s_res_logo != NULL){
			gbitmap_destroy(s_res_logo);
		}
		
		s_res_logo = gbitmap_create_with_resource(TEAM_ICON[x]);
		bitmap_layer_set_bitmap(logo, s_res_logo);
		layer_mark_dirty(bitmap_layer_get_layer(logo));
		
		#ifdef PBL_HEALTH
			s_step_layer = initText((width / 2) - 71, (height / 2) + 18, 110, 28, FONT_KEY_GOTHIC_14_BOLD, s_window);
			text_layer_set_text(s_step_layer, "      ");
			text_layer_set_text_alignment(s_step_layer, GTextAlignmentLeft);
			#ifdef PBL_RECT
				s_td_layer = initText((width / 2) - 57, (height / 2) - 9, 9, 50, FONT_KEY_GOTHIC_14_BOLD, s_window);
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
			gbitmap_destroy(s_res_badteam);
		}
		s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[randTeamBad]);
		bitmap_layer_set_bitmap(beatteam, s_res_badteam);
		layer_mark_dirty(bitmap_layer_get_layer(beatteam));

	}
	else{
		if(s_res_badteam != NULL){
			gbitmap_destroy(s_res_badteam);
		}
		s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[x]);
		bitmap_layer_set_bitmap(beatteam, s_res_badteam);
		layer_mark_dirty(bitmap_layer_get_layer(beatteam));
	}
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "inbox_received_callback()");
	Layer *window_layer = window_get_root_layer(s_window);
	bool configurationInbox = false;

	if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Memory Free: %d", heap_bytes_free());}
	if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Memory Used: %d", heap_bytes_used());}
	
	//Animation Data
	Tuple *animation_t = dict_find(iter, MESSAGE_KEY_ANIMATION);
	if(animation_t) {
		configurationInbox = true;
		int vAnimation = atoi(animation_t->value->cstring);
		if(vAnimation == 0){
			persist_write_int(PER_ANIMATION, 1);
			persist_write_bool(PER_AUTOANIMATION, false);
			runAnimation = 1;
			autoAni = false;
		}
		else if(vAnimation == 1){
			persist_write_int(PER_ANIMATION, 0);
			persist_write_bool(PER_AUTOANIMATION, false);
			runAnimation = 0;
			autoAni = false;
		}
		else if(vAnimation == 2){
			persist_write_int(PER_ANIMATION, 1);
			persist_write_bool(PER_AUTOANIMATION, true);
			runAnimation = 1;
			autoAni = true;
		}
  }
	Tuple *autorange_t = dict_find(iter, MESSAGE_KEY_AUTORANGE);
	if(autorange_t){
		int vAutorange = autorange_t->value->int32;
		autoRange = vAutorange;
		persist_write_int(PER_AUTORANGE, vAutorange);
	}
	Tuple *quite_t = dict_find(iter, MESSAGE_KEY_QUIET);
	if(quite_t){
		bool vQuite = quite_t->value->int32 == 1;
		quiet = vQuite;
		persist_write_bool(PER_QUIET, vQuite);
	}
	Tuple *qstart_t = dict_find(iter, MESSAGE_KEY_QSTART);
	if(qstart_t) {
		int shiftStart = 0;
		if(strlen(qstart_t->value->cstring) == 5){
			shiftStart = 3;
		}
		else if(strlen(qstart_t->value->cstring) == 4){
			shiftStart = 2;
		}
		char *a = qstart_t->value->cstring + shiftStart;
		int vQstart = atoi(qstart_t->value->cstring);
		vQstart = (vQstart * 100) + atoi(a);
		startQ = vQstart;
		persist_write_int(PER_QSTART, vQstart);
	}
	Tuple *qend_t = dict_find(iter, MESSAGE_KEY_QEND);
	if(qend_t) {
		int shiftEnd = 0;
		if(strlen(qend_t->value->cstring) == 5){
			shiftEnd = 3;
		}
		else if(strlen(qend_t->value->cstring) == 4){
			shiftEnd = 2;
		}
		char *b = qend_t->value->cstring + shiftEnd;
		int vQend = atoi(qend_t->value->cstring);
		vQend = (vQend * 100) + atoi(b);
		endQ = vQend;
		persist_write_int(PER_QEND, vQend);
	}
	
	//Bluetooth Data
	Tuple *disconnect_t = dict_find(iter, MESSAGE_KEY_DISCONNECT);
	if(disconnect_t){
		int vDisconnect = atoi(disconnect_t->value->cstring);
		persist_write_int(PER_DISCONNECT, vDisconnect);
		discon = vDisconnect;
	}
	Tuple *reconnect_t = dict_find(iter, MESSAGE_KEY_RECONNECT);
	if(reconnect_t){
		int vReconnect = atoi(reconnect_t->value->cstring);
		persist_write_int(PER_RECONNECT, vReconnect);
		recon = vReconnect;
	}
	
	//Team Data
	Tuple *window_t = dict_find(iter, MESSAGE_KEY_WINDOW);
	if(window_t){
		int vWindow = atoi(window_t->value->cstring);
		mainWindow = vWindow;
		persist_write_int(PER_WINDOW, vWindow);
	}
	Tuple *team_t = dict_find(iter, MESSAGE_KEY_TEAM);
	if(team_t){
		int vTeam = atoi(team_t->value->cstring);
		team = vTeam;
		if(team == 143){
			premium = true;
		}
		persist_write_int(PER_TEAM, team);
	}
	Tuple *badteam_t = dict_find(iter, MESSAGE_KEY_BADTEAM);
	if(badteam_t){
		int vBadteam = atoi(badteam_t->value->cstring);
		badteam = vBadteam;
		if(team == 143){
			premium = true;
		}
		persist_write_int(PER_BADTEAM, badteam);
	}
	
	//Countdown Data
	Tuple *countdown_t = dict_find(iter, MESSAGE_KEY_COUNTDOWN);
	if(countdown_t){
		bool vCountdown = countdown_t->value->int32 == 1;
		if(!vCountdown){
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
	}
	Tuple *countdowndefault_t = dict_find(iter, MESSAGE_KEY_COUNTDOWNDEFAULT);
	if(countdowndefault_t) {
		int vCountdowndefault = atoi(countdowndefault_t->value->cstring);
		countdownDEFAULT = vCountdowndefault;
		persist_write_int(PER_COUNTDOWNDEFAULT, vCountdowndefault);
  }
	Tuple *gametime_t = dict_find(iter, MESSAGE_KEY_GAMETIME);
	if(gametime_t) {
		int shiftGTime = 0;
		if(strlen(gametime_t->value->cstring) == 5){
			shiftGTime = 3;
		}
		else if(strlen(gametime_t->value->cstring) == 4){
			shiftGTime = 2;
		}
		char *c = gametime_t->value->cstring + shiftGTime;
		int vGametime = atoi(gametime_t->value->cstring);
		vGametime = (vGametime * 100) + atoi(c);
		if(vGametime > 12){
			gameapm = 1;
		}
		else{
			gameapm = 0;
		}
		persist_write_int(PER_GAMEAPM, gameapm);
		
		gametime = vGametime / 100;
		gamemin = vGametime - (gametime * 100);
		persist_write_int(PER_GAMEMIN, gamemin);
		
		if(gametime > 12){
			gametime = gametime - 12;
		}
		else if(gametime == 0){
			gametime = gametime + 12;
		}
		persist_write_int(PER_GAMETIME, gametime);
	}
	Tuple *gameday_t = dict_find(iter, MESSAGE_KEY_GAMEDAY);
	if(gameday_t) {
		char *vGamemonth = gameday_t->value->cstring + 5;
		char *vGameday = gameday_t->value->cstring + 8;
		int vGameyear = atoi(gameday_t->value->cstring);
		gameyear = vGameyear;
		persist_write_int(PER_GAMEYEAR, gameyear);
		gamemonth = atoi(vGamemonth);
		persist_write_int(PER_GAMEMONTH, gamemonth);
		gameday = atoi(vGameday);
		persist_write_int(PER_GAMEDAY, gameday);
	}
	Tuple *countdownani_t = dict_find(iter, MESSAGE_KEY_COUNTDOWNANI);
	if(countdownani_t) {
		int vCountdownani = atoi(countdownani_t->value->cstring);
		if(vCountdownani == 0){
			countdownAni = 0;
			persist_write_int(PER_COUNTDOWNANI, 0);
		}
		else if(vCountdownani == 1){
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
  }
	
	//Health Data
	Tuple *steps_t = dict_find(iter, MESSAGE_KEY_STEPS);
	if(steps_t){
		bool vSteps = steps_t->value->int32 == 1;
		if(!vSteps){
			persist_write_bool(PER_STEPS, false);
			healthS = false;
			if(healthSHistory){
				text_layer_set_text(s_step_layer, "      ");
				healthSHistory = false;
			}
		}
		else{
			persist_write_bool(PER_STEPS, true);
			healthS = true;
			premium = true;
			if(!healthSHistory){
				health_handler(time_start_of_today(), time(NULL), 0);
				healthSHistory = true;
			}
		}
	}
	Tuple *td_t = dict_find(iter, MESSAGE_KEY_TD);
	if(td_t){
		bool vTD = td_t->value->int32 == 1;
		if(!vTD){
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
		else{
			persist_write_bool(PER_TD, true);
			healthTD = true;
			premium = true;
			if(!healthTDHistory){
				bitmap_layer_set_bitmap(ftbl, s_res_ftbl);
				layer_mark_dirty(bitmap_layer_get_layer(ftbl));
				healthTDHistory = true;
			}
		}
	}
	
	//Version Data
	Tuple *version_t = dict_find(iter, MESSAGE_KEY_VERSION);
	if(version_t) {
		int vVersion = atoi(version_t->value->cstring);
		if(vVersion != version && !outdated){
			
			#ifdef PBL_COLOR
				s_res_update = gbitmap_create_with_resource(RESOURCE_ID_update);
			#else
				
			#endif
			APP_LOG(APP_LOG_LEVEL_DEBUG, "Outdated");
			outdated = true;
			bitmap_layer_set_bitmap(logo, s_res_update);
			layer_mark_dirty(bitmap_layer_get_layer(logo));
		}
  }
	
	if(configurationInbox){
		if(premium){
			int32_t result = kiezelpay_get_status();
			if(result & KIEZELPAY_LICENSED){
				paid = true;
				persist_write_bool(PER_PAID, paid);
				if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Paid");}
			}
			else{
				paid = false;
				persist_write_bool(PER_PAID, paid);
				if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Not Paid");}

				#ifdef PBL_PLATFORM_APLITE
				#else
				kiezelpay_start_purchase();
				#endif
			}

		}

		if(mainWindow == 0){
			if(runAniHist || windowHist == 1){
				if(s_beat_layer != NULL){
					text_layer_destroy(s_beat_layer);
				}
				if(s_beatbox_layer != NULL){
					layer_destroy(s_beatbox_layer);
				}
			}
			windowHist = 0;
			
			if(s_res_badteam != NULL){
				gbitmap_destroy(s_res_badteam);
				s_res_badteam = NULL;
			}

			if(!outdated){
				setTeam(team, 0, window_layer);
			}

			if(runAnimation == 1){
				setbadTeam(badteam);
				runAniHist = true;
				if(!animationsRunning){
					animationSetup();
				}
				else{
					
					#ifdef PBL_RECT
						s_beatbox_layer = layer_create(GRect(0, 0, 55, 32));
					#elif PBL_ROUND
						s_beatbox_layer = layer_create(GRect(63, 0, 55, 32));
					#endif
					layer_set_update_proc(s_beatbox_layer, beat_update_proc);
					layer_add_child(window_layer, s_beatbox_layer);
					#ifdef PBL_RECT
						GRect to_rect = GRect(0, -35, 55, 32);
					#elif PBL_ROUND
						GRect to_rect = GRect(63, -35, 55, 32);
					#endif
					s_beatbox_animation = property_animation_create_layer_frame(s_beatbox_layer, NULL, &to_rect);
					animation_schedule((Animation*) s_beatbox_animation);

					#ifdef PBL_RECT
						s_beat_layer = initText(0, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
					#elif PBL_ROUND
						s_beat_layer = initText(63, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
					#endif
					text_layer_set_text(s_beat_layer, "BEAT");
					s_beat_animation = property_animation_create_layer_frame(text_layer_get_layer(s_beat_layer), NULL, &to_rect);
					animation_schedule((Animation*) s_beat_animation);
				}
			}
			else{
				runAniHist = false;
			}
		}
		else {
			if(runAniHist){
				if(s_beat_layer != NULL){
					text_layer_destroy(s_beat_layer);
				}
				if(s_beatbox_layer != NULL){
					layer_destroy(s_beatbox_layer);
				}
			}
			windowHist = 1;

			if(!outdated){
				setTeam(badteam, 1, window_layer);
			}
			if(runAnimation == 1){
				setbadTeam(team);
				runAniHist = true;
				if(!animationsRunning){
					animationSetup();
				}
				else{
					#ifdef PBL_RECT
						s_beatbox_layer = layer_create(GRect(0, -35, 55, 32));
					#elif PBL_ROUND
						s_beatbox_layer = layer_create(GRect(63, -35, 55, 32));
					#endif
					layer_set_update_proc(s_beatbox_layer, beat_update_proc);
					layer_add_child(window_layer, s_beatbox_layer);
					#ifdef PBL_RECT
						GRect to_rect = GRect(0, 0, 55, 32);
					#elif PBL_ROUND
						GRect to_rect = GRect(63, 0, 55, 32);
					#endif
					s_beatbox_animation = property_animation_create_layer_frame(s_beatbox_layer, NULL, &to_rect);
					animation_schedule((Animation*) s_beatbox_animation);

					#ifdef PBL_RECT
						s_beat_layer = initText(0, -35, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
					#elif PBL_ROUND
						s_beat_layer = initText(63, -35, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
					#endif
					text_layer_set_text(s_beat_layer, "BEAT");
					s_beat_animation = property_animation_create_layer_frame(text_layer_get_layer(s_beat_layer), NULL, &to_rect);
					animation_schedule((Animation*) s_beat_animation);
				}
			}
			else{
				runAniHist = false;
				#ifdef PBL_RECT
					s_beatbox_layer = layer_create(GRect(0, 0, 55, 32));
				#elif PBL_ROUND
					s_beatbox_layer = layer_create(GRect(63, 0, 55, 32));
				#endif
				layer_set_update_proc(s_beatbox_layer, beat_update_proc);
				layer_add_child(window_layer, s_beatbox_layer);

				#ifdef PBL_RECT
					s_beat_layer = initText(0, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
				#elif PBL_ROUND
					s_beat_layer = initText(63, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
				#endif
				text_layer_set_text(s_beat_layer, "BEAT");
				}
		}
		if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Memory Free: %d", heap_bytes_free());}
		if(debug){APP_LOG(APP_LOG_LEVEL_INFO, "Memory Used: %d", heap_bytes_used());}

		update_time();
		configurationInbox = false;
	}
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

static void main_window_load(Window *window) {
	if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Main Window Loading...");}
	
	#ifdef PBL_PLATFORM_APLITE
		runAnimation = 0;
	#endif
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
		windowHist = 0;
		setTeam(team, 0, window_layer);
		if(runAnimation == 1){
			s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[badteam]);
		}
	}
	else{
		windowHist = 1;
		setTeam(badteam, 1, window_layer);
		if(runAnimation == 1){
			s_res_badteam = gbitmap_create_with_resource(TEAM_ICON[team]);
		}
		else{
			#ifdef PBL_RECT
				s_beatbox_layer = layer_create(GRect(0, 0, 55, 32));
			#elif PBL_ROUND
				s_beatbox_layer = layer_create(GRect(63, 0, 55, 32));
			#endif
			layer_set_update_proc(s_beatbox_layer, beat_update_proc);
			layer_add_child(window_layer, s_beatbox_layer);

			#ifdef PBL_RECT
				s_beat_layer = initText(0, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
			#elif PBL_ROUND
				s_beat_layer = initText(63, 0, 55, 32, FONT_KEY_GOTHIC_28_BOLD, s_window);
			#endif
			text_layer_set_text(s_beat_layer, "BEAT");
		}
	}
	
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
	
	if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Main Window Finished");}
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
		if(s_beat_layer != NULL){
			text_layer_destroy(s_beat_layer);
		}
		if(s_beatbox_layer != NULL){
			layer_destroy(s_beatbox_layer);
		}
		if(s_badteambox_layer != NULL){
			layer_destroy(s_badteambox_layer);
		}
	}

	if(mainWindow == 1 && !animationsRunning){
		if(s_beat_layer != NULL){
			text_layer_destroy(s_beat_layer);
		}
		if(s_beatbox_layer != NULL){
			layer_destroy(s_beatbox_layer);
		}
	}
	
	#ifdef PBL_PLATFORM_APLITE
	#else
	if(!paid){
		countdown = 4;
		persist_write_int(PER_COUNTDOWN, countdown);
		badteam = 20;
		persist_write_int(PER_BADTEAM, badteam);
		team = 0;
		persist_write_int(PER_TEAM, team);
		persist_write_bool(PER_TD, false);
		healthTD = false;
		if(healthTDHistory){
			healthTDHistory = false;
		}
		persist_write_bool(PER_STEPS, false);
		healthS = false;
		if(healthSHistory){
			healthSHistory = false;
		}
		kiezelpay_cancel_purchase();
	}
	#endif
	
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
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 1: %d", runAnimation);}
	}
	if(persist_exists(PER_DISCONNECT)){
		discon = persist_read_int(PER_DISCONNECT);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 2: %d", discon);}
	}
	if(persist_exists(PER_RECONNECT)){
		recon = persist_read_int(PER_RECONNECT);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 3: %d", recon);}
	}
	if(persist_exists(PER_TEAM)){
		team = persist_read_int(PER_TEAM);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 4: %d", team);}
	}
	if(persist_exists(PER_BADTEAM)){
		badteam = persist_read_int(PER_BADTEAM);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 5: %d", badteam);}
	}
	if(persist_exists(PER_WINDOW)){
		mainWindow = persist_read_int(PER_WINDOW);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 6: %d", mainWindow);}
	}
	if(persist_exists(PER_COUNTDOWN)){
		countdown = persist_read_int(PER_COUNTDOWN);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 7: %d", countdown);}
	}
	if(persist_exists(PER_COUNTDOWNDEFAULT)){
		countdownDEFAULT = persist_read_int(PER_COUNTDOWNDEFAULT);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 8: %d", countdownDEFAULT);}
	}
	if(persist_exists(PER_COUNTDOWNANI)){
		countdownAni = persist_read_int(PER_COUNTDOWNANI);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 9: %d", countdownAni);}
	}
	if(persist_exists(PER_RANDOM)){
		random = persist_read_int(PER_RANDOM);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 10: %d", random);}
	}
	if(persist_exists(PER_RANDTEAM)){
		randTeam = persist_read_int(PER_RANDTEAM);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 11: %d", randTeam);}
	}
	if(persist_exists(PER_GAMEDAY)){
		gameday = persist_read_int(PER_GAMEDAY);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 12: %d", gameday);}
	}
	if(persist_exists(PER_DAYSINCE)){
		daysince = persist_read_int(PER_DAYSINCE);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 13: %d", daysince);}
	}
	if(persist_exists(PER_DELAY)){
		delay = persist_read_int(PER_DELAY);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 14: %d", delay);}
	}
	if(persist_exists(PER_GAMETIME)){
		gametime = persist_read_int(PER_GAMETIME);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 15: %d", gametime);}
	}
	if(persist_exists(PER_GAMEMIN)){
		gamemin = persist_read_int(PER_GAMEMIN);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 16: %d", gamemin);}
	}
	if(persist_exists(PER_GAMEMONTH)){
		gamemonth = persist_read_int(PER_GAMEMONTH);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 17: %d", gamemonth);}
	}
	if(persist_exists(PER_GAMEAPM)){
		gameapm = persist_read_int(PER_GAMEAPM);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 18: %d", gameapm);}
	}
	if(persist_exists(PER_GAMEYEAR)){
		gameyear = persist_read_int(PER_GAMEYEAR);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 19: %d", gameyear);}
	}
	if(persist_exists(PER_RANDOMBAD)){
		randombad = persist_read_int(PER_RANDOMBAD);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 20: %d", randombad);}
	}
	if(persist_exists(PER_RANDTEAMBAD)){
		randTeamBad = persist_read_int(PER_RANDTEAMBAD);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 21: %d", randTeamBad);}
	}
	if(persist_exists(PER_DAYSINCE2)){
		daysince2 = persist_read_int(PER_DAYSINCE2);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 22: %d", daysince2);}
	}
	if(persist_exists(PER_QUIET)){
		quiet = persist_read_bool(PER_QUIET);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 23: %d", quiet);}
	}
	if(persist_exists(PER_QSTART)){
		startQ = persist_read_int(PER_QSTART);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 24: %d", startQ);}
	}
	if(persist_exists(PER_QEND)){
		endQ = persist_read_int(PER_QEND);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 25: %d", endQ);}
	}
	if(persist_exists(PER_AUTORANGE)){
		autoRange = persist_read_int(PER_AUTORANGE);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 26: %d", autoRange);}
	}	
	if(persist_exists(PER_AUTOANIMATION)){
		autoAni = persist_read_bool(PER_AUTOANIMATION);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 27: %d", autoAni);}
	}
	if(persist_exists(PER_STEPS)){
		healthS = persist_read_bool(PER_STEPS);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 28: %d", healthS);}
	}	
	if(persist_exists(PER_TD)){
		healthTD = persist_read_bool(PER_TD);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 29: %d", healthTD);}
	}
	if(persist_exists(PER_PAID)){
		paid = persist_read_bool(PER_PAID);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Got 30: %d", paid);}
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
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Seconds Set");}
	}
	else{
		//This is here for the just in case
		tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
		if(debug){APP_LOG(APP_LOG_LEVEL_DEBUG, "Minutes Set");}
	}
	
	// Subscribe to js data
	//app_message_register_inbox_received(inbox);
	events_app_message_request_inbox_size(256);
	events_app_message_request_outbox_size(256);
	
	#ifdef PBL_PLATFORM_APLITE
	#else
  // Listen for KiezelPay events
  kiezelpay_set_event_handler(kiezelpay_event_callback);

  // Initiate KiezelPay
  kiezelpay_init();
	#endif
  
  // The pebble-events package is used for appmessages, check https://www.npmjs.com/package/pebble-events on how to receive your own appmessages as well
  events_app_message_open();

	// Configure your own AppMessage settings for the pebble-events package if you also need app messages
	events_app_message_register_inbox_received(inbox_received_callback, NULL);
	events_app_message_register_inbox_dropped(inbox_dropped_callback, NULL);
	events_app_message_register_outbox_sent(outbox_sent_callback, NULL);
	events_app_message_register_outbox_failed(outbox_failed_callback, NULL);
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