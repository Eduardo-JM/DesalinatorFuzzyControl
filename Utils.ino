float maxOfAll(int numArgs, ...) {
    va_list args;
    va_start(args, numArgs);
    
    float temp = va_arg(args, double);
    for (int i = 1; i < numArgs; ++i) {
        float current = va_arg(args, double);
        if (current > temp)
            temp = current;
    }
    
    va_end(args);
    return temp;
}
