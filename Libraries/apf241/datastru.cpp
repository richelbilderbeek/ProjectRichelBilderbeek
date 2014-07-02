#include <cstdio>
#include "ap.h"


using namespace std;


// The datastruct class member functions

// Construct a datastruct from scratch: size, allocated data
// Possibly fill the rest of it with zeros
datastruct::datastruct (size_t newsize, modint *newdata, int newlocation, int fill)
{
    size = newsize;

    if (newlocation == DEFAULT)
        location = (size <= Memorytreshold ? MEMORY : DISK);
    else location = newlocation;

    if (location == MEMORY)
    {
        if (size)
        {
            if (newdata) data = newdata;
            else
            {
                data = new modint[newsize];
                assert (data);
                if (fill)
                    for (size_t t = 0; t < newsize; t++)
                        data[t] = 0;
            }
        }
        else data = 0;
    }
    else
    {
        fileno = fno++;
        fs = new fstream ();
        if (size)
        {
            fs->open (filename (fileno), ios::out | ios::BIN | ios::trunc);
            assert (fs->good ());
            if (newdata)
            {
                fs->write ((char *) newdata, sizeof (modint) * newsize);
                assert (fs->good ());
                delete[] newdata;
            }
            else if (fill)
            {
                size_t p = newsize, l, b;

                b = (newsize < Maxblocksize ? newsize : Maxblocksize);
                data = new modint[b];
                assert (data);
                for (l = 0; l < b; l++)
                    data[l] = 0;
                while (p)
                {
                    l = (p < b ? p : b);
                    p -= l;
                    fs->write ((char *) data, sizeof (modint) * l);
                    assert (fs->good ());
                }
                delete[] data;
            }
            fs->close ();
        }
        data = 0;
    }

    gotdata = false;
}

// Construct a datastruct from another datastruct,
// possibly with different size and/or location, padded with zeros to some size
datastruct::datastruct (datastruct &d, size_t newsize, int newlocation, size_t padsize)
{
    if (newsize == (size_t) DEFAULT)
        size = d.size;
    else size = newsize;

    if (newlocation == DEFAULT)
        location = d.location;
    else location = newlocation;

    if (padsize == (size_t) DEFAULT)
        padsize = size;

    if (location == MEMORY)
    {
        if (padsize)
        {
            size_t t, p, l, r, getsize = (d.size < size ? d.size : size);
            modint *newdata;

            data = new modint[padsize];
            assert (data);

            p = getsize;
            r = 0;
            while (p)
            {
                l = (p < Blocksize ? p : Blocksize);
                p -= l;
                newdata = d.getdata (r, l);

                moveraw (data + r, newdata, l);

                r += l;
                d.cleardata ();
            }
            for (t = getsize; t < padsize; t++)
                data[t] = 0;
        }
        else data = 0;
    }
    else
    {
        fileno = fno++;
        fs = new fstream ();
        if (size)
        {
            size_t getsize = (d.size < size ? d.size : size);
            size_t b, l, p, r;

            fs->open (filename (fileno), ios::out | ios::BIN | ios::trunc);
            assert (fs->good ());

            p = getsize;
            r = 0;
            while (p)
            {
                l = (p < Maxblocksize ? p : Maxblocksize);
                p -= l;
                data = d.getdata (r, l);
                r += l;
                fs->write ((char *) data, sizeof (modint) * l);
                assert (fs->good ());
                d.cleardata ();
            }

            p = padsize - getsize;
            if (p)
            {
                b = (p < Maxblocksize ? p : Maxblocksize);
                data = new modint[b];
                assert (data);
                for (l = 0; l < b; l++)
                    data[l] = 0;
                while (p)
                {
                    l = (p < b ? p : b);
                    p -= l;
                    fs->write ((char *) data, sizeof (modint) * l);
                    assert (fs->good ());
                }
                delete[] data;
            }
            fs->close ();
        }
        data = 0;
    }

    size = padsize;

    gotdata = false;
}

datastruct::~datastruct ()
{
    assert (!gotdata);

    if (location == MEMORY)
    {
        if (data) delete[] data;
    }
    else
    {
        remove (filename (fileno));
        delete fs;
    }
}

// Allocate a buffer for reading or updating
modint *datastruct::getdata (size_t getposition, size_t getsize)
{
    assert (!gotdata);

    gotdata = true;

    if (location == MEMORY)
    {
        if (data) return data + getposition;
        else return 0;
    }
    else
    {
        assert (!data);
        position = getposition;
        blocksize = getsize;
        data = new modint[getsize];
        assert (data);
        fs->open (filename (fileno), ios::in | ios::BIN);
        assert (fs->good ());
        fs->seekg (sizeof (modint) * getposition);
        assert (fs->good ());
        fs->read ((char *) data, sizeof (modint) * getsize);
        assert (fs->good ());
        fs->close ();
        return data;
    }
}

// Update allocated buffer
void datastruct::putdata (void)
{
    assert (gotdata);

    if (location != MEMORY)
    {
        assert (data);
        fs->open (filename (fileno), ios::in | ios::out | ios::BIN);
        assert (fs->good ());
        fs->seekp (sizeof (modint) * position);
        assert (fs->good ());
        fs->write ((char *) data, sizeof (modint) * blocksize);
        assert (fs->good ());
        fs->close ();
        delete[] data;
        data = 0;
    }

    gotdata = false;
}

// Allocate a buffer for writing
modint *datastruct::readydata (size_t getposition, size_t getsize)
{
    assert (!gotdata);

    gotdata = true;

    if (location == MEMORY)
    {
        if (data) return data + getposition;
        else return 0;
    }
    else
    {
        assert (!data);
        position = getposition;
        blocksize = getsize;
        data = new modint[getsize];
        assert (data);
        return data;
    }
}

// Deallocate a read buffer
void datastruct::cleardata (void)
{
    assert (gotdata);

    if (location != MEMORY && data)
    {
        delete[] data;
        data = 0;
    }

    gotdata = false;
}

// Open a stream for accessing the file of a disk-based datastruct
fstream &datastruct::openstream (void)
{
    assert (location != MEMORY);

    fs->open (filename (fileno), ios::in | ios::out | ios::BIN);
    assert (fs->good ());

    return *fs;
}

// Close the opened stream
void datastruct::closestream (void)
{
    assert (location != MEMORY);

    fs->close ();
}

// Resize the data
void datastruct::resize (size_t newsize)
{
    assert (!gotdata);

    if (location == MEMORY)
    {
        if (newsize)            // Always reallocate, otherwise there'll be problems
        {
            size_t t, s;
            modint *newdata = new modint[newsize];
            assert (newdata);

            s = (size < newsize ? size : newsize);

            moveraw (newdata, data, s);
            for (t = s; t < newsize; t++)
                newdata[t] = 0;

            if (data) delete[] data;
            data = newdata;
        }
        else
        {
            if (data) delete[] data;
            data = 0;
        }
    }
    else
    {
        assert (!data);
        if (newsize > size)
        {
            size_t p = newsize - size, l, b;

            b = (p < Maxblocksize ? p : Maxblocksize);
            data = new modint[b];
            assert (data);
            for (l = 0; l < b; l++)
                data[l] = 0;
            fs->open (filename (fileno), ios::in | ios::out | ios::BIN);
            assert (fs->good ());
            fs->seekp (sizeof (modint) * size);
            assert (fs->good ());
            while (p)
            {
                l = (p < b ? p : b);
                p -= l;
                fs->write ((char *) data, sizeof (modint) * l);
                assert (fs->good ());
            }
            fs->close ();
            delete[] data;
            data = 0;
        }
        else if (newsize < size)
        {
            truncate (filename (fileno), sizeof (modint) * newsize);
        }
    }

    size = newsize;
}

// Relocate the data, possibly also resizing
void datastruct::relocate (int newlocation, size_t newsize)
{
    assert (!gotdata);

    if (newsize == (size_t) DEFAULT)
        newsize = size;
    else if (newsize < size)
        size = newsize;

    if (newlocation == DEFAULT)
        newlocation = (newsize <= Memorytreshold ? MEMORY : DISK);

    if (location == MEMORY && newlocation != MEMORY)
    {
        fileno = fno++;
        fs = new fstream ();
        if (size)
        {
            assert (data);
            fs->open (filename (fileno), ios::out | ios::BIN | ios::trunc);
            assert (fs->good ());
            fs->write ((char *) data, sizeof (modint) * size);
            assert (fs->good ());
            fs->close ();
        }
        if (data) delete[] data;

        if (newsize > size)
        {
            size_t p = newsize - size, l, b;

            b = (p < Maxblocksize ? p : Maxblocksize);
            data = new modint[b];
            assert (data);
            for (l = 0; l < b; l++)
                data[l] = 0;
            fs->open (filename (fileno), ios::in | ios::out | ios::BIN);
            assert (fs->good ());
            fs->seekp (sizeof (modint) * size);
            assert (fs->good ());
            while (p)
            {
                l = (p < b ? p : b);
                p -= l;
                fs->write ((char *) data, sizeof (modint) * l);
                assert (fs->good ());
            }
            fs->close ();
            delete[] data;
        }
        data = 0;
        size = newsize;
        location = newlocation;
    }
    else if (location != MEMORY && newlocation == MEMORY)
    {
        size_t t;

        assert (!data);

        if (newsize)
        {
            data = new modint[newsize];
            assert (data);
            fs->open (filename (fileno), ios::in | ios::BIN);
            assert (fs->good ());
            fs->read ((char *) data, sizeof (modint) * size);
            assert (fs->good ());
            fs->close ();
        }
        else data = 0;
        remove (filename (fileno));
        delete fs;

        for (t = size; t < newsize; t++)
            data[t] = 0;

        size = newsize;
        location = newlocation;
    }
    else
        this->resize (newsize);
}

// Set the data to be the data in the file, destroy previous content
void datastruct::capture (const char *newfilename)
{
    int i;

    assert (!gotdata);

    if (location == MEMORY)
    {
        if (data) delete[] data;
        data = 0;
        fileno = fno++;
        fs = new fstream ();
        location = DISK;                    // Now essentially relocated on disk
    }

    remove (filename (fileno));             // Move on top of file if it exists

    i = rename (newfilename, filename (fileno));
    assert (!i);

    fstream &fs = openstream ();
    fs.seekg (0, ios::end);                 // Get file size
    size = (size_t) fs.tellg () / sizeof (modint);  // Rounds down in case of extra data at and of file
    closestream ();
}

// Move the datastruct to disk, rename the data file and clear the datastruct
void datastruct::release (const char *newfilename)
{
    int i;

    assert (!gotdata);

    relocate (DISK);

    remove (newfilename);                   // Move on top of new filename if it exists

    i = rename (filename (fileno), newfilename);
    assert (!i);

    location = MEMORY;                      // File no longer belongs to this datastruct
    size = 0;
    delete fs;
}
