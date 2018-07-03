#include <libgpsmm.h>
int main(int argc, char *argv[])
{
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
    return 0;
}
