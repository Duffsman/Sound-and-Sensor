#ifndef _button_h
#define _button_h

class Button
{
public:
    Button(uint8_t pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT_PULLUP);
    }

    Button() {}

    bool update(bool val)
    {
        static uint8_t state = 0;
        state = (state << 1);
        state |= val;
        state |= 0xFE;
        debounced_state = (state == 0xFF);
        return (state == 0xFF);
    }

    bool update()
    {
        uint8_t val = digitalRead(pin);
        return update(val);
    }

    bool rose()
    {
        static bool prev = true;
        if (!prev && debounced_state)
        {
            prev = debounced_state;
            return true;
        }
        else
        {
            prev = debounced_state;
            return false;
        }
    }

    bool fell()
    {
        static bool prev = false;
        if (prev && !debounced_state)
        {
            prev = debounced_state;
            return true;
        }
        else
        {
            prev = debounced_state;
            return false;
        }
    }

    bool state(){
        return debounced_state;
    }

private:
    bool debounced_state = true;
    uint8_t pin;
};

#endif
