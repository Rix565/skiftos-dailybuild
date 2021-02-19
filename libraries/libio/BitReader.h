#pragma once

#include <libio/Reader.h>
#include <libutils/Vector.h>

namespace IO
{

class BitReader
{
private:
    Reader &_reader;

    uint_fast32_t _bit_buffer = 0;
    uint8_t _bit_count = 0;

    void fill()
    {
    }

public:
    inline BitReader(Reader &reader)
        : _reader{reader}
    {
    }

    inline void skip_bits(size_t num_bits)
    {
        _bit_count += num_bits;
    }

    inline uint16_t grab_uint16()
    {
        uint16_t result = _data[_index / 8] + (_data[(_index / 8) + 1] << 8);

        _index += 16;

        return result;
    }

    inline uint8_t peek_bit()
    {
        return (_data[_index / 8] & (1 << (_index % 8))) ? 1 : 0;
    }

    inline unsigned int grab_bits(unsigned int num_bits)
    {
        unsigned int result = 0;

        for (unsigned int i = 0; i != num_bits; i++)
        {
            result |= (unsigned int)peek_bit() << i;
            _index++;
        }

        return result;
    }

    inline unsigned int peek_bits(size_t num_bits)
    {
        unsigned int cached_index = _index;
        unsigned int result = grab_bits(num_bits);
        _index = cached_index;
        return result;
    }

    inline uint32_t grab_bits_reverse(size_t num_bits)
    {
        assert(num_bits <= 32);

        uint32_t ret_val = 0;
        for (size_t i = 0; i != num_bits; i++)
        {
            ret_val |= (uint32_t)peek_bit() << ((num_bits - 1) - i);
            _index++;
        }

        return ret_val;
    }

    inline unsigned int peek_bits_reverse(size_t num_bits)
    {
        unsigned int cached_index = _index;
        unsigned int result = grab_bits_reverse(num_bits);

        _index = cached_index;

        return result;
    }
};

} // namespace IO
