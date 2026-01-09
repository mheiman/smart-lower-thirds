#define LOG_TAG "[" PLUGIN_NAME "][main]"
#include "core.hpp"
#include "dock.hpp"
#include "websocket_bridge.hpp"

#include <obs-frontend-api.h>
#include <obs-module.h>
#include <obs.h>

#include <QTimer>

OBS_DECLARE_MODULE();
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

static bool g_deferred_init_done = false;

static void on_frontend_event(enum obs_frontend_event event, void *)
{
	if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING && !g_deferred_init_done) {
		g_deferred_init_done = true;
		LOGI("OBS finished loading, running deferred initialization");
		smart_lt::rebuild_and_swap();
		smart_lt::cleanup_old_html_files();
	}
}

MODULE_EXPORT const char *obs_module_name(void)
{
	return PLUGIN_NAME;
}

MODULE_EXPORT const char *obs_module_description(void)
{
	return "Smart Lower Thirds Plugin v" PLUGIN_VERSION;
}

bool obs_module_load(void)
{
	LOGI("Plugin loaded (version %s)", PLUGIN_VERSION);

	smart_lt::init_from_disk();
	LowerThird_create_dock();
	obs_frontend_add_event_callback(on_frontend_event, nullptr);
	return true;
}

void obs_module_post_load(void)
{
	smart_lt::ws::init();

	// Rebuild HTML from lt-state.json after OBS has finished startup checks
	QTimer::singleShot(2000, []() {
		if (smart_lt::has_output_dir()) {
			smart_lt::rebuild_and_swap();
		}
	});

	if (auto *dock = LowerThird_get_dock()) {
		QTimer::singleShot(250, dock, [dock]() { dock->refreshBrowserSources(); });
		QTimer::singleShot(1000, dock, [dock]() { dock->refreshBrowserSources(); });
	}
}

void obs_module_unload(void)
{
	LOGI("Unloading plugin %s", PLUGIN_NAME);

	obs_frontend_remove_event_callback(on_frontend_event, nullptr);

	smart_lt::ws::shutdown();

	LowerThird_destroy_dock();

	LOGI("Plugin %s unloaded", PLUGIN_NAME);
}
