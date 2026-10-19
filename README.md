# Lab 0 – Zephyr RTOS Warm-Up with native_sim

**Course:** Embedded Systems (CO3053) – Class CC01
**Lecturer:** Pham Hoang Anh
**Student:** Vo Minh Quan – 2353022

## Workout Training Timer

5 exercises × 30 s, with 5 s rest between consecutive exercises (no rest after exercise 5) → total **170 s**.
Implemented with `printk()` and `k_sleep(K_SECONDS(1))` only (no busy-wait).

## Repository structure

```
workout_timer/
├── CMakeLists.txt
├── prj.conf
└── src/main.c
workout_log.txt      # console output of the --rt run
```

## Build & run

```bash
cd ~/zephyrproject/zephyr
west build -p always -b native_sim workout_timer -d build/workout_native

# real-time pacing (~170 s)
/usr/bin/time -f "REAL TIME: %e s" ./build/workout_native/zephyr/zephyr.exe --rt

# fast logic check
./build/workout_native/zephyr/zephyr.exe --no-rt
```

## Result

| Run mode  | Kernel time (`k_uptime_get`) | Wall-clock time |
|-----------|------------------------------|-----------------|
| `--rt`    | 170.170 s                    | 170.21 s        |
| `--no-rt` | 170.170 s                    | 0.032 s         |

Environment: Ubuntu 24.04 (WSL2), Zephyr v4.5.0-rc2, Zephyr SDK 1.0.1, west 1.5.0.
