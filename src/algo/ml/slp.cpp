#include "slp.h"

nl::ml::SLP::SLP() {
      printf("SLP initialized!\n");

      printf("data => h: %d, w: %d\n", data.height(), data.width());
      for(int j=0; j<data.height(); j++) {
            for(int i=0; i<data.width(); i++) {
                  printf("data[%d][%d]: %lf\n", j, i, data.get_point(j, i));
            }
      }

      // debug
      printf("labels => size: %d\n", labels.size());
      for(int i=0; i<labels.size(); i++)
            printf("labels[%d]: %d\n", i, labels.get_point(i));

      printf("weights => size: %d\n", weights.size());
      for(int i=0; i<weights.size(); i++)
            printf("weights[%d]: %lf\n", i, weights.get_point(i));
}
