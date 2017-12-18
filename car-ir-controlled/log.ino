void logMsg(const char *fmt, ...) {
    va_list args;
    char buffer[128];

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    Serial.println(buffer);
    va_end(args);
}
