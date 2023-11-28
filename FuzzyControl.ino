/**
 * This method sets all membership degrees
 * to zero
 * @param m membership to clear
 */
void clearMembershipDegrees(membership m) {
  m.very_low = 0;
  m.low = 0;
  m.medium = 0;
  m.high = 0;
  m.very_high = 0;
}

membership seawater_temperature_membership;
membership heated_seawater_temperature_membership;
membership solar_receiver_temperature_membership;
membership flow_membership;

function_limits seawater_limits = {5, 10, 13, 20, 27, 30, 35};
function_limits heated_seawater_limits = {30, 40, 40, 50, 60, 65, 70};
function_limits solar_receiver_limits = {40, 60, 60, 80, 100, 100, 120};

/**
 * This method sets all membership degrees of all 
 * fuzzy variables to zero
 */
void clearAllMemberships() {
  clearMembershipDegrees(seawater_temperature_membership);
  clearMembershipDegrees(heated_seawater_temperature_membership);
  clearMembershipDegrees(solar_receiver_temperature_membership);
  clearMembershipDegrees(flow_membership);
}

/**
 * This method inits the fuzzy control parameters
 */
void initFuzzyControl(){
  clearAllMemberships();
}
/**
 * @returns the minimum of the two fuzzy vars
*/ 
float fuzzyAnd(float a, float b) {
  return fmin(a,b);
}

/**
 * @returns the maximum of the two fuzzy vars
*/
float fuzzyOr(float a, float b) {
  return fmax(a,b);
}

/**
 * @returns 1 - the value of the fuzzy var
*/
float fuzzyNot(float a) {
  return 1 - a;
}

/**
 * This normal distribution only applies for the categories
 * from low temperature to high temperature since the others
 * have different function shape
 * @param x value to search
 * @param mu mean
 * @param b upper bound
 * @returns the degrees of membership of the seawater in the specified range
 */
float getNormalDistributionValue(float x, float mu, enum DISTRIBUTION_SIGMA sigma){
  float r = pow(
        exp(1), 
        -pow(x - mu, 2) / (2*pow(sigma, 2))
  );
  return r < ROUND_TO_ZERO_IF_LOWER_THAN ? 0 : r;
}

/**
 * This S shape distribution only applies for the categorie
 * very_high since the other categories have different function shapes
 * @param x value to search
 * @param a lower bound
 * @param b upper bound
 * @returns the degrees of membership of the element in the specified range
 */
float getSShapeDistributionValue(float x, float a, float b){
  if (x > b) return 1;
  if (x < a) return 0;
  float r = (x - a)/((float)(b-a));
  return r < ROUND_TO_ZERO_IF_LOWER_THAN ? 0 : r;
}

/**
 * This Z shape distribution only applies for the categorie
 * very_low since the other categories have different function shapes
 * @param x value to search
 * @param a lower bound
 * @param b upper bound
 * @returns the degrees of membership of the element in the specified range
 */
float getZShapeDistributionValue(float x, float a, float b){
  if (x > b) return 0;
  if (x < a) return 1;
  float r = 1 - (b-x)/((float)(b - a));
  return r < ROUND_TO_ZERO_IF_LOWER_THAN ? 0 : r;
}

/**
 * @param temperature reference temperature
 * @param limits membership curves limits
 * @param m membership data struct
 * @param sigma Standard deviation of the normal distribution
*/
void setMembership(
    float temperature,
    function_limits limits, 
    membership m,
    enum DISTRIBUTION_SIGMA sigma
) {
  m.very_low = getZShapeDistributionValue(
    temperature,
    limits.lower_limit_very_low,
    limits.upper_limit_very_low
  );
  m.low = getNormalDistributionValue(
    temperature,
    limits.mean_low,
    sigma
  );
  m.medium = getNormalDistributionValue(
    temperature,
    limits.mean_medium,
    sigma
  );
  m.high = getNormalDistributionValue(
    temperature,
    limits.mean_high,
    sigma
  );
  m.very_high = getSShapeDistributionValue(
    temperature,
    limits.lower_limit_very_high,
    limits.upper_limit_very_high
  );
}

/**
 * This method sets all FuzzyMemberships using
 * the sensors' data
 */
void setFuzzyMemberships() {
  clearAllMemberships();
  setMembership(
    readTemperature(SEAWATER_TEMPERATURE_SENSOR),
    seawater_limits,
    seawater_temperature_membership,
    SEAWATER_NORMAL_DISTRIBUTION_SIGMA
  );
  setMembership(
    readTemperature(HEATED_SEAWATER_TEMPERATURE_SENSOR),
    heated_seawater_limits,
    heated_seawater_temperature_membership,
    HEATED_SEAWATER_NORMAL_DISTRIBUTION_SIGMA
  );
  setMembership(
    readTemperature(SOLAR_RECEIVER_TEMPERATURE_SENSOR),
    solar_receiver_limits,
    solar_receiver_temperature_membership,
    SOLAR_RECEIVER_NORMAL_DISTRIBUTION_SIGMA
  );
  if (!activateFlow()) {
    
    return;
  }
  /*TODO: defuzzyfy send flow command to the pump*/
}

/**
 * When we trye
 */
void setMaxOfTwo(float * current_membership, float new_membership){
  if (new_membership > *current_membership)
    *current_membership = new_membership;
}

bool activateFlow(){
  float temp;
  /**
   * ***************************************************
   * ***************************************************
   * ****            SUPERIOR RULES                 ****
   * ***************************************************
   * ***************************************************
   */
  /* If SRT is very low, then flow is zero*/
  if (solar_receiver_temperature_membership.very_low >= 0)
    return false;
  /* If SRT is low AND ST is (low OR very low), then flow is zero*/
  if (
    fuzzyAnd(
      solar_receiver_temperature_membership.low,
      fuzzyOr(
        seawater_temperature_membership.low,
        seawater_temperature_membership.very_low
      )
    ) >= 0
  )
    return false;
  /* If HST is very_high AND SRT is (very high OR high), then flow is very high */
  if (
    fuzzyAnd(
      heated_seawater_temperature_membership.very_high,
      fuzzyOr(
        solar_receiver_temperature_membership.very_high,
        solar_receiver_temperature_membership.high
      )
    ) >= 0
   ) {
    setMaxOfTwo(&flow_membership.very_high, heated_seawater_temperature_membership.very_high);
   }
  /* If HST is very_high AND SRT is (medium high OR low), then flow is high */
   if (
    (temp = fuzzyAnd(
      heated_seawater_temperature_membership.very_high,
      fuzzyOr(
        solar_receiver_temperature_membership.medium,
        solar_receiver_temperature_membership.low
      )
    )) >= 0
   ) {
    setMaxOfTwo(&flow_membership.high, temp);
  }
  /**
   * ***************************************************
   * ***************************************************
   * ****             GENERAL RULES                 ****
   * ***************************************************
   * ***************************************************
   */
  /* If SRT is low but not very low AND ST is very_high, then flow is very low */
   if (
    (temp = fuzzyAnd(
      solar_receiver_temperature_membership.low,
      seawater_temperature_membership.very_high
    )) >= 0
   ) {
    if (solar_receiver_temperature_membership.very_low == 0)
      setMaxOfTwo(&flow_membership.very_low, temp);
  }
  /* If SRT is medium AND ST is very low, then flow is very low*/
  if (
    (temp = fuzzyAnd(
      solar_receiver_temperature_membership.medium,
      seawater_temperature_membership.very_low
    )) >= 0
   ) {
    if (solar_receiver_temperature_membership.very_low == 0)
      setMaxOfTwo(&flow_membership.very_low, temp);
  }
  /* If SRT is medium AND ST is low, then flow is low*/
  if (
    (temp = fuzzyAnd(
      solar_receiver_temperature_membership.medium,
      seawater_temperature_membership.low
    )) >= 0
   ) {
    setMaxOfTwo(&flow_membership.low, temp);
  }
  /* If SRT is medium or High AND ST is low, then flow is medium*/
  if (
    (temp = fuzzyAnd(
      fuzzyOr(
        solar_receiver_temperature_membership.medium,
        solar_receiver_temperature_membership.high
      ),
      seawater_temperature_membership.low
    )) >= 0
   ) {
    setMaxOfTwo(&flow_membership.medium, temp);
  }
  /* If SRT is medium or High AND ST is low, then flow is medium*/
  if (
    (temp = fuzzyAnd(
      solar_receiver_temperature_membership.medium
      seawater_temperature_membership.low
    )) >= 0
   ) {
    setMaxOfTwo(&flow_membership.medium, temp);
  }
  return true;
}
