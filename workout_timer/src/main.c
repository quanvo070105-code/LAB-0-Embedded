#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#ifdef CONFIG_ARCH_POSIX
#include "posix_board_if.h"   /* posix_exit() - chỉ có trên native_sim */
#endif

#define NUM_EXERCISES     5
#define EXERCISE_TIME_S   30
#define REST_TIME_S       5

/* Đếm ngược 'seconds' giây, mỗi giây in một dòng */
static void countdown(const char *label, int seconds)
{
	for (int remaining = seconds; remaining > 0; remaining--) {
		printk("%s: %d s\n", label, remaining);
		k_sleep(K_SECONDS(1));   /* thread ngủ, nhường CPU - không busy-wait */
	}
}

int main(void)
{
	int64_t start_ms = k_uptime_get();

	for (int exercise = 1; exercise <= NUM_EXERCISES; exercise++) {
		printk("\nExercise %d/%d START\n", exercise, NUM_EXERCISES);
		countdown("Training", EXERCISE_TIME_S);
		printk("Exercise %d COMPLETE\n", exercise);

		if (exercise < NUM_EXERCISES) {      /* không nghỉ sau bài 5 */
			countdown("Rest", REST_TIME_S);
		}
	}

	int64_t elapsed_ms = k_uptime_get() - start_ms;
	printk("\n=== WORKOUT COMPLETED ===\n");
	printk("Total time: %lld.%03lld s\n", elapsed_ms / 1000, elapsed_ms % 1000);

#ifdef CONFIG_ARCH_POSIX
	posix_exit(0);   /* native_sim: thoát chương trình khi xong */
#endif
	return 0;
}
