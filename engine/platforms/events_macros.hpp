#pragma once

    // Raccourcis macros pour les fonctions utilisants un argument EventFt<>
template <typename ReturnType, typename ... Arguments>
using EventFt     = ReturnType(*)(Arguments ...);

#define USE_EVENT             template <typename __EventFt_ReturnType__, typename ... __EventFt_Arguments__>
#define TypeOfEvent           __EventFt_ReturnType__
#define DeclarEvent(varName)  EventFt<__EventFt_ReturnType__, __EventFt_Arguments__ ...> varName, __EventFt_Arguments__ ... __EventFt_Packages__
#define PlayEvent( varName )  varName(__EventFt_Packages__ ...);
#define ArgsOfEvent           __EventFt_Arguments__ ...

    // Raccourcis macros pour les fonctions utilisants un argument EventFtVoid<>
template <typename ReturnType>
using EventFtVoid = ReturnType(*)();

#define USE_VOID_EVENT         template <typename __EventFt_ReturnType__>
#define DeclarVoidEvent(varName)  EventFtVoid<__EventFt_ReturnType__> varName
#define PlayVoidEvent( varName )  varName();
#define ArgsOfEvent           __EventFt_Arguments__ ...

#define CALLBACK             USE_EVENT TypeOfEvent
#define CALLBACK_VOID        USE_VOID_EVENT TypeOfEvent