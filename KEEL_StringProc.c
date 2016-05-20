
int KEEL_FindChar(char* buffer, int startIndex, int targetChar, int lenLimit)
{
    int i;

    if(startIndex >= 0)
    {
        i = startIndex;
    }
    else
    {
        return -1;
    }

    while(buffer[i] != targetChar)
    {
        if(buffer[i] == '\0')
        {
            return -1;
        }
        else
        {
            i++;
        }

        if(i >= lenLimit)
        {
            return -1;
        }
    }

    return i;
}
