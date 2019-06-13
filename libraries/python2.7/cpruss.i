/* cpruss.i */
 %module pypruss
 %{
 /* Put header files here or function declarations like below */
 extern void start(int n);
 extern void stop(int n);
 extern void restart(int n);
 extern char* state(int n);
 extern int check_module(char *module);
 extern void modprobe();
 extern int rmmod(int n);
 extern void make(char *path);
 extern void load_firmware(char *path, int n);
 extern void modprobe_pru_rproc();
 extern void modprobe_rpmsg_pru();
 extern int rmmod_pru_rproc(int n);
 extern int rmmod_rpmsg_pru(int n);
 extern int send_msg(char *message, int n);
 extern char* get_msg(int n);
 %}
 
 extern void start(int n);
 extern void stop(int n);
 extern void restart(int n);
 extern char* state(int n);
 extern int check_module(char *module);
 extern void modprobe();
 extern int rmmod(int n);
 extern void make(char *path);
 extern void load_firmware(char *path, int n);
 extern void modprobe_pru_rproc();
 extern void modprobe_rpmsg_pru();
 extern int rmmod_pru_rproc(int n);
 extern int rmmod_rpmsg_pru(int n);
 extern int send_msg(char *message, int n);
 extern char* get_msg(int n);
