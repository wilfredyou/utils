enum {
    ecc_good = 0,
    ecc_no_correction = 1,
    ecc_corrected = 2,
    ecc_unorrectable = 3
}Result_e;

// MIPI Alliance Specification for CSI-2 data bit [63:0]
static const uint64_t ecc_parity[8] = {0x0422D5844BF12CB7ULL,  
                                 0x0844EA8895F2555BULL,  
                                 0x1089F31126749A6DULL,  
                                 0x21117C2238B8E38EULL,  
                                 0x421EB043C0DF03F0ULL,  
                                 0x83E0307C00EFFC00ULL,  
                                 0xFC00C07FFF000000ULL,  
                                 0xFFFF0F8000000000ULL}; 



// MIPI Alliance Specification for CSI-2
uint8_t Calc_Ecc(const uint8_t *inPtr)
{
    uint8_t ret = 0;
    uint8_t i, j;

    uint64_t input = 0;

    for (i = 0; i < 8; i++) {
        input |= ((uint64_t)inPtr[i]) << (8 * i);
    }

    for (i = 0; i < 8; i++) {
        uint8_t parityBit = 0;
        uint64_t inputBits = input & ecc_parity[i];
        // XOR all the bits in inputBits together
        for (j = 0; j < 64; j++) {
            parityBit ^= (uint8_t)((inputBits >> j) & (uint64_t)1);
        }

        ret |= (parityBit << i);
    }

    return ret;
}


// MIPI Alliance Specification for CSI-2
Result_e Check_Ecc(uint8_t *inPtr, uint8_t ecc)
{
    uint8_t i,j;
    uint8_t syn = ecc ^ Calc_Ecc(inPtr);

    if (syn == 0) {
        return ecc_good;
    }

    // If the syndrome is one of the rows of the identity matrix I, then one of the parity bits are in error, no correction required
    if ((syn & (syn - 1)) == 0) {
        return ecc_no_correction;
    }

    // Search via EccParity table looking for a syndrome
    for (i = 0; i < 64; i++) {
        uint8_t val = 0;
        uint64_t mask = (uint64_t)1 << i;
        for (j = 0; j < 8; j++) {
            val |= ((ecc_parity[j] & mask) >> i) << j;
        }
        if (syn == val) {
            // i -> the bit position to correct
            inPtr[i / 8] ^= (uint8_t)1 << (i % 8);
            return ecc_corrected;
        }
    }

    return ecc_uncorrectable;
}

