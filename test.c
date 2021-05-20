/*
 * Generates random text.
 *
 * @param len       Amount of random text to generate
 * @param out_text  [OUT] Random text. Must be at least 'len' in size
 *
 * @return          Size of the random text on success, else -1
 */
int generate_random_text(int len, char *out_text)
{
    int res = -1;

    if (out_text != nullptr)
    {
        ifstream ifs("/dev/urandom", ifstream::in);

        if (ifs)
        {
            unsigned char buf[len] = { 0 };

            ifs.read((char*)buf, len - 1);

            if (ifs.gcount() == len - 1)
            {
                STRING_HANDLE sh = nullptr;
                BUFFER_HANDLE bh = BUFFER_new();
                BUFFER_build(bh, buf, len);

                sh = Base64_Encoder(bh);
                strncpy(out_text, STRING_c_str(sh), len);
                res = len;
                NB_LOG_VERBOSE("rand txt [%s]\n", out_text);

                STRING_delete(sh);
                BUFFER_delete(bh);
            }

            ifs.close();
        }
    }

    return res;
}
