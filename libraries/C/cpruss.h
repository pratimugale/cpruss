//Function prototypes
//The n in the parameter stands for which PRU you currently want to use
//n = 1: PRU 1: /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state
//n = 2: PRU 2: /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state

void start(int n);
void stop(int n);
void restart(int n);
char* state(int n);
int check_module();
void modprobe();
int rmmod(int n);
void make(char *path);

// Global Variables
/*char command[150];
int prun;
char status[8];*/
