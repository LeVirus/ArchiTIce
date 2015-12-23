// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.1
//
// <auto-generated>
//
// Generated from file `interface.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

package biblAudio;

public class Morceau implements java.lang.Cloneable, java.io.Serializable
{
    public String msNomMorceau;

    public String msFichier;

    public int muiDateSortie;

    public int muiDureeMorceau;

    public Morceau()
    {
        msNomMorceau = "";
        msFichier = "";
    }

    public Morceau(String msNomMorceau, String msFichier, int muiDateSortie, int muiDureeMorceau)
    {
        this.msNomMorceau = msNomMorceau;
        this.msFichier = msFichier;
        this.muiDateSortie = muiDateSortie;
        this.muiDureeMorceau = muiDureeMorceau;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
        if(this == rhs)
        {
            return true;
        }
        Morceau _r = null;
        if(rhs instanceof Morceau)
        {
            _r = (Morceau)rhs;
        }

        if(_r != null)
        {
            if(msNomMorceau != _r.msNomMorceau)
            {
                if(msNomMorceau == null || _r.msNomMorceau == null || !msNomMorceau.equals(_r.msNomMorceau))
                {
                    return false;
                }
            }
            if(msFichier != _r.msFichier)
            {
                if(msFichier == null || _r.msFichier == null || !msFichier.equals(_r.msFichier))
                {
                    return false;
                }
            }
            if(muiDateSortie != _r.muiDateSortie)
            {
                return false;
            }
            if(muiDureeMorceau != _r.muiDureeMorceau)
            {
                return false;
            }

            return true;
        }

        return false;
    }

    public int
    hashCode()
    {
        int __h = 5381;
        __h = IceInternal.HashUtil.hashAdd(__h, "::biblAudio::Morceau");
        __h = IceInternal.HashUtil.hashAdd(__h, msNomMorceau);
        __h = IceInternal.HashUtil.hashAdd(__h, msFichier);
        __h = IceInternal.HashUtil.hashAdd(__h, muiDateSortie);
        __h = IceInternal.HashUtil.hashAdd(__h, muiDureeMorceau);
        return __h;
    }

    public Morceau
    clone()
    {
        Morceau c = null;
        try
        {
            c = (Morceau)super.clone();
        }
        catch(CloneNotSupportedException ex)
        {
            assert false; // impossible
        }
        return c;
    }

    public void
    __write(IceInternal.BasicStream __os)
    {
        __os.writeString(msNomMorceau);
        __os.writeString(msFichier);
        __os.writeInt(muiDateSortie);
        __os.writeInt(muiDureeMorceau);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
        msNomMorceau = __is.readString();
        msFichier = __is.readString();
        muiDateSortie = __is.readInt();
        muiDureeMorceau = __is.readInt();
    }

    static public void
    __write(IceInternal.BasicStream __os, Morceau __v)
    {
        if(__v == null)
        {
            __nullMarshalValue.__write(__os);
        }
        else
        {
            __v.__write(__os);
        }
    }

    static public Morceau
    __read(IceInternal.BasicStream __is, Morceau __v)
    {
        if(__v == null)
        {
             __v = new Morceau();
        }
        __v.__read(__is);
        return __v;
    }
    
    private static final Morceau __nullMarshalValue = new Morceau();

    public static final long serialVersionUID = 4364456256687275181L;
}
