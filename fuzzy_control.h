#ifndef FUZZY_CONTROL_H
#define FUZZY_CONTROL_H

#define ROUND_TO_ZERO_IF_LOWER_THAN 0.08
#define FUZZY_STEP 0.05

enum DISTRIBUTION_SIGMA {
  SEAWATER_NORMAL_DISTRIBUTION_SIGMA = 3,
  HEATED_SEAWATER_NORMAL_DISTRIBUTION_SIGMA = 4,
  SOLAR_RECEIVER_NORMAL_DISTRIBUTION_SIGMA = 8
};

/**
 * @brief Struct to store the membership degrees for different 
 * categories.
 */
typedef struct membership_degrees {
  float very_low;
  float low;
  float medium;
  float high;
  float very_high;
} membership;

/**
 *
*/
typedef struct function_limits {
  int lower_limit_very_low;
  int upper_limit_very_low;
  int mean_low;
  int mean_medium;
  int mean_high;
  int lower_limit_very_high;
  int upper_limit_very_high;
} function_limits;

typedef struct output_limits {
  int lower_limit_very_low;
  int upper_limit_very_low;
  int lower_limit_low;
  int upper_limit_low;
  int lower_limit_medium;
  int upper_limit_medium;
  int lower_limit_high;
  int upper_limit_high;
  int lower_limit_very_high;
  int upper_limit_very_high;
} output_limits;


float getNormalDistributionValue(float, float, enum DISTRIBUTION_SIGMA);
void setMembership(float, struct function_limits, struct membership_degrees, enum DISTRIBUTION_SIGMA);
void setMaxOfTwo(float *, float);
float defuzzify();
float maxOfAll(float ...);

#endif
