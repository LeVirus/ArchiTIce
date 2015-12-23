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

public interface _ServeurIceOperations
{
    void afficherMorceaux(Ice.Current __current);

    Morceau bRechercherMorceau(String sNomMusique, Ice.Current __current);

    boolean bAjoutMorceau(String sNomArt, String sNomMorc, String sFic, int uiDureeMorc, int uiDateSortie, Ice.Current __current);

    boolean bSuprMorceau(String sNomMorc, Ice.Current __current);

    Morceau[] getMorceaux(String sNomArt, Ice.Current __current);
}
