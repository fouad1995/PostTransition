#include "office.h"
void print_all_packages(town t) {
  int i = 0, j = 0;
  printf("%s:\n", t.name);
  for (i = 0; i < t.offices_count; i++) {

    // print office count
    printf("\t%d:\n", i);
    // print packages in office count
    for (j = 0; j < t.offices[i].packages_count; j++) {
      printf("\t\t%s\n", t.offices[i].packages[j].id);
    }
  }
}

void send_all_acceptable_packages(town *source, int source_office_index,
                                  town *target, int target_office_index) {
  int i = 0, j = 0;
  int SPackegeNum;
  int TPackegeNum;
  int min_weight = target->offices[target_office_index].min_weight;
  int max_weight = target->offices[target_office_index].max_weight;
  // check the weight of the destination to know how much
  // package should be added

  for (i = 0; i < source->offices[source_office_index].packages_count; i++) {

    if (source->offices[source_office_index].packages[i].weight >= min_weight &&
        source->offices[source_office_index].packages[i].weight <= max_weight) {
      TPackegeNum = target->offices[target_office_index].packages_count;

      // increase the size of target packages by 1
      target->offices[target_office_index].packages =
        (package*)  realloc(target->offices[target_office_index].packages,
                  (TPackegeNum + 1) * sizeof(package));

      // transfer the package from source to target
      target->offices[target_office_index].packages[TPackegeNum] =
          source->offices[source_office_index].packages[i];

      // remove the package from the source
      SPackegeNum = source->offices[source_office_index].packages_count;

      for (j = i; j < SPackegeNum - 1; j++) {
        source->offices[source_office_index].packages[j] =
            source->offices[source_office_index].packages[j + 1];
      }
      // decrease the size of source packages by 1
      source->offices[source_office_index].packages =
          (package *)realloc(source->offices[source_office_index].packages,
                             (SPackegeNum - 1) * sizeof(package));

      // decrease the count of packages in source and
      // increase it in target
      (target->offices[target_office_index].packages_count)++;
      (source->offices[source_office_index].packages_count)--;
      i--;

    } 
  }
}

town town_with_most_packages(town *towns, int towns_count) {
  int i = 0, j = 0, sum = 0, sum1 = 0;
  int index = 0, max = 0;
  for (int i = 0; i < towns_count; i++) {
    int sum = 0;
    for (int j = 0; j < towns[i].offices_count; j++) {
      sum += towns[i].offices[j].packages_count;
    }
    if (sum > max) {
      max = sum;
      index = i;
    }
  }
  return towns[index];
}

town *find_town(town *towns, int towns_count, char *name) {
  int i;
  for (i = 0; i < towns_count; i++) {
    if (!(strcmp(towns[i].name, name)))
      break;
  }
  return towns + i;
}