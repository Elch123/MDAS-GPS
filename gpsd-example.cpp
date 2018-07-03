//  Example C++ gpsd program using libgpsmm

//  Has no actual purpose other than output some of libgpsmm struct variables of
//  your choosing.
//  reference declarations: https://fossies.org/dox/gpsd-3.17/index.html
//
//  compiles without warning as follows:
//  g++ -Wall -std=c++14 -pedantic $(pkg-config --cflags --libs libgps) gpsd-example.cpp -o gpsd-example
//  Free for the taking.
//  Version 1.3
// g++ gpsd-example.cpp -L/usr/local/lib/ -lgps --std=c++14
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include <libgpsmm.h>

int main(void)
{
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

  if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    std::cerr << "No GPSD running.\n";
    return 1;
  }

  for (;;) {
    struct gps_data_t *gpsd_data;

    if (!gps_rec.waiting(1000000)) continue;

    if ((gpsd_data = gps_rec.read()) == NULL) {
      std::cerr << "GPSD read error.\n";
      return 1;
    } else {
      while (((gpsd_data = gps_rec.read()) == NULL) ||
             (gpsd_data->fix.mode < MODE_2D)) {
        // Do nothing until fix
    //  std::cout << "error";
      }
      timestamp_t ts   = gpsd_data->fix.time;
      double latitude  = gpsd_data->fix.latitude;
      double longitude = gpsd_data->fix.longitude;

      // convert GPSD's timestamp_t into time_t
      time_t seconds;
      seconds = (time_t)ts;
      auto tm = *std::localtime(&seconds);

      std::ostringstream oss;
      oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
      auto time_str = oss.str();

      // set decimal precision
      std::cout.precision(6);
      std::cout.setf(std::ios::fixed, std::ios::floatfield);
      std::cout << time_str << "," <<
        latitude << "," <<
        longitude << '\n';
    }
  }
  return 0;
}
