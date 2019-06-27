#include <px4_config.h>
#include <px4_defines.h>
#include <px4_posix.h>
#include <px4_tasks.h>
#include <uORB/Subscription.hpp>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/uORB.h>


extern "C" __EXPORT int test_boi_main(int argc, char *argv[]);

int main_trampoline(int argc, char *argv[])
{
	PX4_INFO("Test Boi running");

	vehicle_global_position_s pos {
		.timestamp = hrt_absolute_time(),
		.lat = 47.358079,
		.lon = 8.520320,
		.alt = 435.9343,
		.alt_ellipsoid = 483.0439,
		.delta_alt = 0.0,
		.vel_n = 0,
		.vel_e = 0,
		.vel_d = 0,
		.yaw = -1.3427,
		.eph = 1.5457,
		.epv = 1.4574,
		.terrain_alt = 0,
		.lat_lon_reset_counter = 2,
		.alt_reset_counter = 0,
		.terrain_alt_valid = false,
		.dead_reckoning = false
	};

	auto adv = orb_advertise(ORB_ID(vehicle_global_position), &pos);

	//orb_publish(ORB_ID(vehicle_global_position), adv, &pos);

	px4_usleep(10000000);

	orb_unadvertise(adv);

	PX4_INFO("Test boi done");

	return 0;
}

int test_boi_main(int argc, char *argv[])
{
	if (argc < 2) {
		warnx("usage: test_boi {test}");
		return 1;
	}

	if (!strcmp(argv[1], "test")) {
		px4_task_spawn_cmd("testboi", SCHED_DEFAULT, SCHED_PRIORITY_MAX, 1000, (px4_main_t) main_trampoline, nullptr);

	}

	return 0;
}
