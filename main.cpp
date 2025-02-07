#include <pico/stdlib.h>

class GPIOPin {
public:
    GPIOPin(int pin, bool input = true, bool pullup = true, bool invert = false) : pin_number(pin) {
        gpio_init(pin_number);
        gpio_set_dir(pin_number, !input);  // true for out, false for in
        if (input && pullup) {
            gpio_pull_up(pin_number);
        }
        if (invert) {
            if (input) {
                gpio_set_inover(pin_number, GPIO_OVERRIDE_INVERT);
            } else {
                gpio_set_outover(pin_number, GPIO_OVERRIDE_INVERT);
            }
        }
        if (!input) {
            gpio_put(pin_number, 0);
        }
    }

    GPIOPin(const GPIOPin &) = delete;

    bool read() {
        return gpio_get(pin_number);
    }

    bool operator()() {
        return read();
    }

    void write(bool value) {
        gpio_put(pin_number, value);
    }

    void operator()(bool value) {
        write(value);
    }

    operator int() {
        return pin_number;
    }

private:
    const int pin_number;
};

const int led_on_time = 100;

void updateLED(GPIOPin &switchPin, GPIOPin &ledPin, bool &ledState, int &ledTimer) {
    if (switchPin.read()) {
        ledPin.write(true);
        ledState = true;
        ledTimer = led_on_time;
    } else if (ledState) {
        if (--ledTimer <= 0) {
            ledPin.write(false);
            ledState = false;
        }
    }
}

int main() {
    stdio_init_all();

    GPIOPin sw0(9, true, true, true);
    GPIOPin sw1(8, true, true, true);
    GPIOPin sw2(7, true, true, true);

    GPIOPin led1(22, false);
    GPIOPin led2(21, false);
    GPIOPin led3(20, false);

    bool led1State = false, led2State = false, led3State = false;
    int led1Timer = 0, led2Timer = 0, led3Timer = 0;

    while (true) {
        updateLED(sw2, led1, led1State, led1Timer);
        updateLED(sw1, led2, led2State, led2Timer);
        updateLED(sw0, led3, led3State, led3Timer);

        sleep_ms(10);
    }

    return 0;
}