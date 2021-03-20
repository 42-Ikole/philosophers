# philosophers
Three solutions to the dining philosophers problem in c

## ✅ usage
use
```sh
make
```
and then run with
```sh
./philo_one {phil amount} {time to die} {time to eat} {time to sleep} [must eat x amount]
```

### ❗ note
- The must eat amount is optional!
- All the time variables are in milliseconds.
- This was made on mac, due to the usage of **usleep** the values have to be modified for it to work on linux!

### 💤 code
**Philo one:**
  - Uses mutex locks and threads.

**Philo two:**
  - Uses semaphores and threads.

**Philo Three:**
  - Uses semaphores, threads and processes.

### ⚠️ bugs
- This project was written on mac, due to differences in how processes work some **usleep** values have to be changed in order to make it work on linux!
