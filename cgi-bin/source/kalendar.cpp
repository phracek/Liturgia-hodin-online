/**************************************************************/
/*                                                            */
/* dbzaltar.cpp                                               */
/* (c)1999-2016 | Juraj Vidéky | videky@breviar.sk            */
/*                                                            */
/* description | contains 'database' of liturgical calendars  */
/*                                                            */
/**************************************************************/

#include "vstudio.h"

#ifndef __KALENDAR_CPP_
#define __KALENDAR_CPP_

#include "dbzaltar.h"
#include "liturgia.h"
#include "myexpt.h"
#include "mylog.h"
#include <string.h>
#include "mystring.h"
#include "breviar.h"

short int sviatky_svatych_01_januar(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	Log("mesiac január\n");
	switch (den){

	case 2: // MES_JAN -- 02JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JAN_02[_global_jazyk], MENO_SVIATKU);
		// 2010-11-22: český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
		if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_UCITEL_CIRKVI);
		}
		else{
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		}
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 3: // MES_JAN -- 03JAN
		// dominikáni majú mnoho vecí naviac; v latinskom je samostatne len ant. pre ben+magn, 2. čítanie a modlitba; aj sk-ofm majú povinnú spomienku

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_najsv_mena_jezisovho_sk_ofm(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_najsv_mena_jezisovho_sk_ofm(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_najsv_mena_jezisovho_sk_ofm(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			_global_svaty1.kalendar = _global_kalendar;
			mystrcpy(_global_svaty1.meno, text_JAN_03[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT); // ??
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk == JAZYK_CZ_OP){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_set_zalmy_najsv_mena_jezisovho_czop(modlitba);
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_VESPERY;
					_set_zalmy_najsv_mena_jezisovho_czop(modlitba);
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				else{
					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_03[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT); // ??
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JAN_03_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 4: // MES_JAN -- 04JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_HU)){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_HU)){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_04_OFM[_global_jazyk], MENO_SVIATKU);
			if (_global_jazyk == JAZYK_SK){
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			}
			else{
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 5: // MES_JAN -- 05JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_05_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JAN_05_CSSR[_global_jazyk], MENO_SVIATKU); // CZ CSsR: 19JUN
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR

		break;

	case 7: // MES_JAN -- 07JAN
		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba; // alebo ako na ranné chvály

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
				_vlastna_cast_modlitba_ina; // alebo ako na vešpery

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

					break;
				}
				pocet = 2;
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_JAN_07[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 8: // MES_JAN -- 08JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_08_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 9: // MES_JAN -- 09JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_09_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 10: // MES_JAN -- 10JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JAN_10_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JAN_10_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 11: // MES_JAN -- 11JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JAN_11_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 12: // MES_JAN -- 12JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
			}
			else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_JAN_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		break;

	case 13: // MES_JAN -- 13JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JAN_13[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 14: // MES_JAN -- 14JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_14_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JAN_14_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JAN_14_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 15: // MES_JAN -- 15JAN

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_JAN_15_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_JAN_15_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SVD)) || ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_SVD))) {
			if (poradie_svaty == 1) {

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full_okrem_hymnu(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_hymnu(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_hymnu(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_15_SVD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SVD, KALENDAR_HU_SVD

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			if (_global_jazyk == JAZYK_CZ){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_LUB_SPOMIENKA_FMA_CZ;
			}
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_15_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else if (_global_jazyk == JAZYK_HU) {
			if (poradie_svaty == 1) {
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_15_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 16: // MES_JAN -- 16JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFM;
			}
			mystrcpy(_global_svaty1.meno, text_JAN_16_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 17: // MES_JAN -- 17JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JAN_17[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 18: // MES_JAN -- 18JAN

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, (_global_jazyk == JAZYK_CZ) ? FORCE_BRAT_HYMNUS : FORCE_NEBRAT);
				// set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_ANTIFONY + FORCE_BRAT_ZALMY + FORCE_BRAT_KCIT_1CIT);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_hymnu(modlitba);
				_set_zalmy_1nedele_rch();
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_marie(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_18_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		else if ((_global_jazyk == JAZYK_HU) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk == JAZYK_HU){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					_vlastna_cast_mcd_ant_kcitresp_modl;
				}

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_full(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
					// _vlastna_cast_modlitba_ina; // Alebo ako na vešpery.
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_full(modlitba);
				}
				else{
					_vlastna_cast_modlitba; // Modlitba ako na ranné chvály alebo na vešpery.
					_vlastna_cast_2citanie;
				}

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_full(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
					_vlastna_cast_modlitba_ina; // Alebo ako na ranné chvály.
				}

				break;
			}
			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			}
			else{
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			}// JAZYK_SK, KALENDAR_SK_OP
			mystrcpy(_global_svaty1.meno, text_JAN_18[_global_jazyk], MENO_SVIATKU); // v maďarsku 18. januára, rovnako SK-OP
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			}
			else{
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}// JAZYK_SK, KALENDAR_SK_OP
		}// HU only, kalendár pre KALENDAR_SK_OP

		break;

	case 19: // MES_JAN -- 19JAN

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty1.meno, text_JAN_18[_global_jazyk]);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_19_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JAN_19_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 20: // MES_JAN -- 20JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if (poradie_svaty == 2){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JAN_20_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		pocet = 2;
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_JAN_20_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty2.farba = LIT_FARBA_CERVENA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			pocet = 3;
			mystrcpy(_global_svaty3.meno, text_JAN_20_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 3){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky

			pocet = 3;
			mystrcpy(_global_svaty3.meno, text_JAN_20_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 21: // MES_JAN -- 21JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_set_zalmy_1nedele_rch();
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}

			modlitba = MODL_POSV_CITANIE;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_set_zalmy_sviatok_muc(modlitba);
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JAN_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 22: // MES_JAN -- 22JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JAN_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_kresponz;
					_vlastna_cast_1citanie;
					_vlastna_cast_2citanie;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_kresponz;
					_vlastna_cast_kcitanie;
					_vlastna_cast_benediktus;
					_vlastna_cast_prosby;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_kresponz;
					_vlastna_cast_kcitanie;
					_vlastna_cast_magnifikat;
					_vlastna_cast_prosby;
				}
				_vlastna_cast_modlitba;

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					_vlastna_cast_mcd_full_okrem_hymnu;
				}

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SPOMIENKA_FMA : LOKAL_SLAV_SPOMIENKA_FMA_CZ;
			mystrcpy(_global_svaty2.meno, text_JAN_22_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JAN_22_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky

			pocet = 2;
			mystrcpy(_global_svaty2.meno, text_JAN_22_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 23: // MES_JAN --23JAN

		if (_global_jazyk == JAZYK_SK){
			// je to spomienka len v Dóme sv. Martina, BA
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_DOM_SV_MARTINA;
			mystrcpy(_global_svaty1.meno, text_JAN_23_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JAN_23_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 24: // MES_JAN -- 24JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			if (_global_jazyk == JAZYK_SK){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SLAVNOST_SDB;
			}
			mystrcpy(_global_svaty1.meno, text_JAN_24_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_24[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 25: // MES_JAN -- 25JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			// nemá popis; 2013-02-04: doplnené
			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_prosieb(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);

			modlitba = MODL_VESPERY;
			_vlastna_cast_full_okrem_prosieb(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_JAN_25[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 26: // MES_JAN -- 26JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JAN_26[_global_jazyk], MENO_SVIATKU);
		// český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
		if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI /* MODL_SPOL_CAST_DUCH_PAST_BISKUP */);
		}
		else{
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		}
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 27: // MES_JAN -- 27JAN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JAN_27[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_VYCH);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JAN_27_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JAN_27_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 28: // MES_JAN --28JAN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				// vlastná psalmódia: Žalm 40, 2–14. 17–18; Žalm 27, 1-6 (chybne v tlačenom propriu uvedené na str. 42: 1–9)
				_set_zalmy_pc_40_27(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_modlitba;

				_set_mcd_doplnkova_psalmodia_z127_131(MODL_POPOLUDNI);

				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_mcd_doplnkova_psalmodia(!je_len_doplnkova_psalmodia(modlitba)); // toto je potrebné z technického dôvodu, pretože doplnková psalmódia bola nastavená ešte pri nastavovaní žaltára (pred vlastnými časťami svätých)

				modlitba = MODL_VESPERY;
				// 2012-02-06: doplnené žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
				_set_zalmy_vesp_127_111_kol(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_JAN_28[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else {
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_28[_global_jazyk], MENO_SVIATKU);

			// ...KNAZ nie je vo vlastnej casti, avsak aby sme vedeli, co mame dat v tych castiach, ktore nie su v uciteloch cirkvi, kde sa odvolava na duchovnych pastierov; 23/02/2000A.D.
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);
					// 2010-07-06: doplnené žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					set_zalm(1, modlitba, "z1.htm", "ZALM1");
					set_zalm(2, modlitba, "z21.htm", "ZALM21");
					set_zalm(3, modlitba, "z92.htm", "ZALM92");

					_vlastna_cast_mcd_kcitresp_modl;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_JAN_28[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 29: // MES_JAN -- 29JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SVD)) || ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_SVD))) {
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_vlastna_cast_full_okrem_hymnu(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_hymnu(modlitba);

				break;
			}
			if (_global_jazyk == JAZYK_SK) {
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			else {
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			}// (_global_jazyk == JAZYK_HU)
			mystrcpy(_global_svaty1.meno, text_JAN_29_SVD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SVD, KALENDAR_HU_SVD

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_29_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA, MODL_SPOL_CAST_SV_ZENA_MANZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 30: // MES_JAN -- 30JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JAN_30_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JAN_30_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 31: // MES_JAN -- 31JAN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_INVITATORIUM;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_mcd_ant_kcitresp_modl;
				}

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_31_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JAN_31[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;
	};

	return pocet;
}// sviatky_svatych_01_januar()

short int sviatky_svatych_02_februar(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_FEB;

	Log("mesiac február\n");
	switch (den){

	case 1: // MES_FEB -- 01FEB

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
					_vlastna_cast_full_okrem_hymnu(modlitba);
				}
				else{
					_vlastna_cast_modlitba;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_FEB_01_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 2: // MES_FEB -- 02FEB

		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// definovanie parametrov pre modlitbu
			if ((poradie_svaty == 1) &&
				(query_type != PRM_DETAILY))
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_obetovania(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_1nedele_rch();

			// MCD: antifóny a žalmy sú z bežného dňa
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastna_cast_mcd_hymnus_kcitresp_modl;
			}
			else{
				_vlastna_cast_mcd_kcitresp_modl;
			}

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_obetovania(modlitba);

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_obetovania(modlitba);

			// kompletórium: prevzaté podľa 06AUG; keďže v liturgicke_obdobie() bolo odvetvené, nič sa pre kompletórium nenastavovalo - doplnené
			modlitba = MODL_KOMPLETORIUM;
			// ak padne tento sviatok na sobotu, kompletórium (po druhých vešperách) má byť nedeľné, po prvých vešperách
			if (_global_den.denvt == DEN_SOBOTA){
				zaltar_kompletorium(DEN_NEDELA /* _global_den.denvt */, _global_den.litobd /* OBD_CEZ_ROK */, ZALTAR_VSETKO /* specialne */, _global_den.tyzzal);
				_global_modl_kompletorium = _global_modl_prve_kompletorium;
			}// DEN_SOBOTA
			else{
				zaltar_kompletorium(_global_den.denvt, _global_den.litobd /* OBD_CEZ_ROK */, ZALTAR_VSETKO /* specialne */, _global_den.tyzzal);
			}// iný deň ako sobota

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.kalendar = _global_kalendar;

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);
		}// kalendár pre KALENDAR_CZ_OPRAEM
		else{
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 5; // sviatky Pána uvedené vo všeobecnom kalendári
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// vešobecný kalendár
		mystrcpy(_global_svaty1.meno, text_FEB_02[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;

		break;

	case 3: // MES_FEB -- 03FEB

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if (poradie_svaty == 2){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_FEB_03_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		pocet = 2;
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_FEB_03_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty2.farba = LIT_FARBA_BIELA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 4){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 5){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_FEB_03_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;

			_global_svaty4.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty4.smer = 12; // ľubovoľné spomienky
			_global_svaty4.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty4.meno, text_FEB_03_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty4.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty4.farba = LIT_FARBA_CERVENA;
			_global_svaty4.kalendar = _global_kalendar;

			pocet = 5;
			_global_svaty5.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty5.smer = 12; // ľubovoľné spomienky
			_global_svaty5.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty5.meno, text_FEB_03_3_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty5.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty5.farba = LIT_FARBA_CERVENA;
			_global_svaty5.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 4: // MES_FEB -- 04FEB

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk == JAZYK_CZ_OP){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_04_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_FEB_04_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_04_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
			}
			else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_FEB_04_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_FEB_04_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

		// 04FEB/05FEB: Popolcová streda nepripadne pred týmto dátumom

	case 5: // MES_FEB -- 05FEB

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);
				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období 
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období 
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg
			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_FEB_05[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 6: // MES_FEB -- 06FEB

		if (poradie_svaty == 1){
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
				file_name_vlastny_kalendar(_global_kalendar);
			}
			else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){
				file_name_vlastny_kalendar(_global_kalendar);
			}
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);
				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období 
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1194-1195, nemá vlastné antifóny; ani SK
				// pre SK OFM resp. CZ OFMCap je vlastná antifóna
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období 
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1194-1195, nemá vlastné antifóny; ani SK
				// pre SK OFM resp. CZ OFMCap je vlastná antifóna
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;
			}// nie je_privileg
			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			mystrcpy(_global_svaty1.meno, text_FEB_06_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}
		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			mystrcpy(_global_svaty1.meno, text_FEB_06_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}
		else{
			mystrcpy(_global_svaty1.meno, text_FEB_06[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}

		break;

	case 7: // MES_FEB -- 07FEB

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12;
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_07_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_FEB_07_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_07_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg
				break;
			}
			if (!(_global_jazyk == JAZYK_HU)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			else{
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.typslav_lokal = LOKAL_SLAV_HU_KLARISSZAKNAL_EM;
			}
			mystrcpy(_global_svaty1.meno, text_FEB_07_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 8: // MES_FEB -- 08FEB

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				_vlastna_cast_modlitba;
			}// nie je_privileg
			break;
		}

		else if (poradie_svaty == 2){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
			}// nie je_privileg
			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_FEB_08_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VYCH, MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		pocet = 2;
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_FEB_08_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
		_global_svaty2.farba = LIT_FARBA_BIELA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 9: // MES_FEB -- 09FEB

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){

			// presúva sa 10FEB na 9. února pre KALENDAR_CZ_OPRAEM
			sprintf(_anchor_head, "%02d%s_", 10, nazov_MES[mesiac]); // MES_FEB
			Log("  _anchor_head == %s\n", _anchor_head);

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					// naviac, ant. na vešpery vo zväzku pre 10.2. chýba; je len v zväzku II... (III predpokladá použitie zo spol. časti)
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_FEB_10[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_09_OFMCAP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SPOMIENKA_FMA : LOKAL_SLAV_SPOMIENKA_FMA_CZ;
			mystrcpy(_global_svaty1.meno, text_FEB_09_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 10: // MES_FEB -- 10FEB

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_opraem_pc_1_8_21(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_FEB_10_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// 2011-02-18: tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// 2011-02-18: tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					// naviac, ant. na vešpery vo zväzku pre 10.2. chýba; je len v zväzku II... (III predpokladá použitie zo spol. časti)
					// 2013-05-13: antifóna veru vo zväzku III nie je vlastná
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_FEB_10[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 11: // MES_FEB -- 11FEB

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_FEB_11[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 12: // MES_FEB -- 12FEB

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_12_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_FEB_12_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 13: // MES_FEB -- 13FEB

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_13_OP[_global_jazyk]);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_FEB_13_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 14: // MES_FEB -- 14FEB

		// na Slovensku aj CZ 5. júla, slávnosť (preto na SK len spomienka); v Európe sviatok (napr. HU); CZ neslávi tento deň vôbec
		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky | 2014-02-14: D. Dian upozornil, že to už nie je vo všeobecnom slovenskom kalendári, iba ako votívna sv. omša (t. j. ani ľubovoľná spomienka)
			_global_svaty1.typslav_lokal = LOKAL_SLAV_14_FEB_CYRIL_METOD;
			mystrcpy(_global_svaty1.meno, text_FEB_14[_global_jazyk], MENO_SVIATKU);
			// český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI // nie je to tu treba, lebo je to vetva len pre SK; ponechané historicky
			if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			}
			else{
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// SK only

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_FEB_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// HU only

		break;

	case 15: // MES_FEB -- 15FEB

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_15_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_15_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 16: // MES_FEB -- 16FEB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_16_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_FEB_16_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 17: // MES_FEB -- 17FEB

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_17_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_17[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 18: // MES_FEB -- 18FEB
		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){

			// presúva sa 17FEB na 18. února pre KALENDAR_CZ_OPRAEM
			sprintf(_anchor_head, "%02d%s_", 17, nazov_MES[mesiac]); // MES_FEB
			Log("  _anchor_head == %s\n", _anchor_head);

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
					// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_FEB_18_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){

					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
						_vlastna_cast_modlitba_spomprivileg_ina;
					}
					else{
						_vlastna_cast_modlitba_spomprivileg;
					}

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
						_vlastna_cast_modlitba_ina;
					}
					else{
						_vlastna_cast_modlitba;
					}
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_18_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_FEB_18_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 19: // MES_FEB -- 19FEB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_19_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_FEB_19_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			mystrcpy(_global_svaty1.meno, text_FEB_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 20: // MES_FEB -- 20FEB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_20_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_FEB_20_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 21: // MES_FEB -- 21FEB

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1208-1210, vlastnú ant. nemá
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1208-1210, vlastnú ant. nemá
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_FEB_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 22: // MES_FEB -- 22FEB
		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_kresp_a_prosieb(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);

			_vlastna_cast_mcd_kcitresp_modl;

			modlitba = MODL_VESPERY;
			_vlastna_cast_full_okrem_kresp_a_prosieb(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_FEB_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 23: // MES_FEB -- 23FEB

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_FEB_23[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 24: // MES_FEB -- 24FEB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_FEB_24_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_FEB_24_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// kalendár pre KALENDAR_SK_OP

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;
				_vlastna_cast_benediktus;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				_vlastna_cast_magnifikat;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_MAJ_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// v HU sa slávi 24.2.; vo všeobecnom kalendári 14.5.

		break;

	case 25: // MES_FEB -- 25FEB

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				// _vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_FEB_25_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;
	};

	return pocet;
}// sviatky_svatych_02_februar()

short int sviatky_svatych_03_marec_04_april(short int den, short int mesiac, short int poradie_svaty, _struct_sc sc){
	short int pom_poradie = 1;

	Log("mesiac marec & apríl\n");

	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	switch (mesiac - 1){

	case MES_MAR:
	Log("mesiac marec\n");
	// najskorší možný dátum veľkonočnej nedele: 22. marec (najneskorší: 25. apríla)

	// kontrola: Veľká noc padne na 22.-26. marca; vtedy je 19. marca vo veľkom týždni, a preto sa prekladá na sobotu pred Kvetnou nedeľou
	if ((_global_den.denvt == DEN_SOBOTA) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr - 8) && (_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 22) && (_global_r._VELKONOCNA_NEDELA.den <= 26)){
		// t.j. slávnosť sv. Jozefa sa prekladá pred veľký týždeň, na sobotu pred Kvetnou nedeľou, ako to bolo v r. 2008
		sprintf(_anchor_head, "%02d%s_", 19, nazov_MES[mesiac - 1]); // MES_MAR
		Log("  _anchor_head == %s\n", _anchor_head);
		Log("(ako rok 2008, sobota 15. marca) jumping to label_19_MAR...\n");
		goto label_19_MAR;
	}// prekladanie: slávnosť sv. Jozefa

	// kontrola: Veľká noc padne na 22.-31. marca; vtedy je 25. marca vo Veľkom týždni, Trojdní resp. Veľkonočnej oktáve, a preto sa prekladá na pondelok po skončení Veľkonočnej oktávy
	if ((_global_den.denvt == DEN_PONDELOK) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr + 8) && (_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 22) && (_global_r._VELKONOCNA_NEDELA.den <= 31)){
		// t.j. slávnosť Zvestovania Pána sa prekladá za Veľkonočnú oktávu, na pondelok po Veľkonočnej oktáve, ako to bolo v r. 2008, 2005, 2002, 1989
		sprintf(_anchor_head, "%02d%s_", 25, nazov_MES[mesiac - 1]); // MES_MAR
		Log("  _anchor_head == %s\n", _anchor_head);
		Log("(ako rok 2008, pondelok 31. marca) jumping to label_25_MAR...\n");
		goto label_25_MAR;
	}// prekladanie: slávnosť Zvestovania Pána

	switch (den){

	case 2: // MES_MAR -- 02MAR
		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

				}// nie je_privileg
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			mystrcpy(_global_svaty1.meno, text_MAR_02_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 4: // MES_MAR -- 04MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1223-1225, vlastnú ant. nemá
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1223-1225, vlastnú ant. nemá
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_04[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}// nie je_privileg

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAR_04_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_MUCENIK);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
			break;
		}// HU only

		break;

	case 7: // MES_MAR -- 07MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1225-1227, vlastnú ant. nemá
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1225-1227, vlastnú ant. nemá
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_MAR_07[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 8: // MES_MAR -- 08MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1227-1229, vlastnú ant. nemá
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1227-1229, vlastnú ant. nemá
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_08[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 9: // MES_MAR -- 09MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1229-1232, vlastnú ant. nemá
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				// tak je to vo zväzku II (pôst+veľká noc); avak v III je to normálne, vlastná ant.; opravené
				// LA LH, vol. III, p. 1229-1232, vlastnú ant. nemá
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_09[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

		// do 9. marca sú propriá vo zväzku III (cezročné obdobie), potom sa pokračuje až dňom 12. mája; zrušené preto časti "else" vetiev if(je_post), lebo nie sú potrebné

	case 10: // MES_MAR -- 10MAR

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAR_10_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				set_popis_dummy();

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_BRATISLAVA;
			mystrcpy(_global_svaty1.meno, text_MAR_10_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		break;

		// 10MAR/11MARFEB: Popolcová streda nepripadne po tomto dátume

	case 12: // MES_MAR -- 02MAR

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAR_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 15: // MES_MAR -- 15MAR

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_MAR_15_CSSR[_global_jazyk], MENO_SVIATKU); // CZ CSsR: 20MAJ
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR

		break;

	case 17: // MES_MAR -- 17MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_17[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					// _vlastna_cast_magnifikat_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_GYOR_EGYH;
			mystrcpy(_global_svaty2.meno, text_MAR_17_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 18: // MES_MAR -- 18MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				// nema modlitba = MODL_VESPERY, lebo su prve vespery slavnosti sv. Jozefa

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_18[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

					// nema modlitba = MODL_VESPERY, lebo su prve vespery slavnosti sv. Jozefa
				}// je_privileg

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAR_18_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 19: // MES_MAR -- 19MAR

	label_19_MAR :

		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// definovanie parametrov pre modlitbu
			if ((poradie_svaty == 1) &&
				(query_type != PRM_DETAILY))
				set_spolocna_cast(sc, poradie_svaty);

			set_popis_dummy();

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_sviatok_sv_muzov(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_sv_muzov(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_sviatok_sv_muzov(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_MAR_19[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 20: // MES_MAR -- 20MAR

		if (_global_den.denvt == DEN_PONDELOK){
			// t.j. slávnosť sv. Jozefa padla na pôstnu nedeľu -- preto sa prekladá na najbližší pondelok (t. j. 20.3.)
			sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]); // MES_MAR
			Log("  _anchor_head == %s\n", _anchor_head);
			Log("jumping to label_19_MAR...\n");
			goto label_19_MAR;
		}
		break;

		// MES_MAR -- 22MAR // 22. marec je najskorší možný dátum veľkonočnej nedele

		// 22MAR/23MAR: Veľká noc nepripadne pred týmto dátumom

	case 23: // MES_MAR -- 23MAR

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v pôste)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;
			}// nie je pôst

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAR_23[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 25: // MES_MAR -- 25MAR

	label_25_MAR :

		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// definovanie parametrov pre modlitbu
			if ((poradie_svaty == 1) &&
				(query_type != PRM_DETAILY))
				set_spolocna_cast(sc, poradie_svaty);

			set_popis_dummy();

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_narodenie(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_obetovania(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
				_vlastna_cast_kresponz_ve;
			}
			else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
				_vlastna_cast_kresponz_po;
			}
			_set_zalmy_narodenie(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_MAR_25[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 26: // MES_MAR -- 26MAR

		if (_global_den.denvt == DEN_PONDELOK){
			// t.j. slávnosť Zvestovania Pána padla na pôstnu nedeľu -- preto sa prekladá na najbližší pondelok (t. j. 26.3.)
			// môže sa stať, že pre dátum VN 25. marca je 26.3. pondelok (Veľkonočný pondelok); vtedy sa ale Zvestovanie prekladá podľa podmienky na začiatku marca
			sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac - 1]); // MES_MAR
			Log("  _anchor_head == %s\n", _anchor_head);
			Log("jumping to label_25_MAR...\n");
			goto label_25_MAR;
		}

		break;
	};

	break; // case MES_MAR

	case MES_APR:
		Log("mesiac apríl\n");

		// kontrola: Veľká noc padne na 24. marca -- 1. apríla; vtedy je 25. marca vo Veľkom týždni, Trojdní resp. Veľkonočnej oktáve, a preto sa prekladá na pondelok po skončení Veľkonočnej oktávy
		// ak padne Veľká noc na 2. apríla a neskôr, 25. marca padne pred Kvetnú nedeľu (teda tam sa nič neprekladá)
		// ToDo: preveriť, ako je to, keď padne VN na 1. apríla (napr. 2018, 2029): či sa Zvestovanie nepreloží o jeden deň prv, teda pred Kvetnú nedeľu?
		if ((_global_den.denvt == DEN_PONDELOK) && (_global_den.denvr == _global_r._VELKONOCNA_NEDELA.denvr + 8) && (((_global_r._VELKONOCNA_NEDELA.mesiac == MES_APR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 1) && (_global_r._VELKONOCNA_NEDELA.den <= 1)) || ((_global_r._VELKONOCNA_NEDELA.mesiac == MES_MAR + 1) && (_global_r._VELKONOCNA_NEDELA.den >= 24) && (_global_r._VELKONOCNA_NEDELA.den <= 31)))){
			// t.j. slávnosť Zvestovania Pána sa prekladá za Veľkonočnú oktávu, na pondelok po Veľkonočnej oktáve, ako to bolo v r. 2008, 2005, 2002, 1989
			sprintf(_anchor_head, "%02d%s_", 25, nazov_MES[MES_MAR]); // MES_MAR -- musí tu byť natvrdo, lebo je to už v mesiaci 'apríl' (na rozdiel od analogickej kontroly na začiatku marca)
			Log("  _anchor_head == %s\n", _anchor_head);
			Log("(rok 2008, pondelok 31. marca) jumping to label_25_MAR...\n");
			sprintf(_file, "sv_%s.htm", nazov_mes[MES_MAR]); // MES_MAR -- musí tu byť natvrdo, lebo je to už v mesiaci 'apríl' (na rozdiel od analogickej kontroly na začiatku marca, kde nie je potrebné nastavovať mená súborov)
			sprintf(_file_pc, "pc_sv_%s.htm", nazov_mes[MES_MAR]); // MES_MAR -- musí tu byť natvrdo, lebo je to už v mesiaci 'apríl' (na rozdiel od analogickej kontroly na začiatku marca, kde nie je potrebné nastavovať mená súborov)
			goto label_25_MAR;
		}// prekladanie: slávnosť Zvestovania Pána

		switch (den){

		case 1: // MES_APR -- 01APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie_spomprivileg;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_01_OCD[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				break;
			}// kalendár pre KALENDAR_SK_OCD

			break;

		case 2: // MES_APR -- 02APR

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1388-1399, uvádza ant. aj pre Veľkonočné obdobie
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1388-1399, uvádza ant. aj pre Veľkonočné obdobie
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_02[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 4: // MES_APR -- 04APR

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1391, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1391, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_04[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 5: // MES_APR -- 05APR

			// pre Slovensko, Česko atď. podľa všeobecného kalendára sv. Vincenta Ferrera, pre dominikánov presunuté na 5.5...; aj pre dominikánov platí všeobecný kalendár
			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1393, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1393, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_05[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 7: // MES_APR -- 07APR

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1395-1396, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1395-1396, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_APR_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 10: // MES_APR -- 10APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_APR_10_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			break;

		case 11: // MES_APR -- 11APR

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1398, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1398, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_APR_11[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 13: // MES_APR -- 13APR

			if (poradie_svaty == 1){
				// na spomienku v privilegovaný deň (spomienka v pôste)
				if (je_privileg){
					if (query_type != PRM_DETAILY)
						set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat_spomprivileg;
					_vlastna_cast_modlitba_spomprivileg;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie_spomprivileg;
					_vlastna_cast_modlitba;

				}// je_privileg
				else{
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					// LA LH, vol. II, p. 1400, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					// LA LH, vol. II, p. 1400, uvádza ant. len "pro commemoratione"
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}// nie je pôst

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_13[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty2.meno, text_APR_13_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			break;

		case 14: // MES_APR -- 14APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_APR_14_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				break;
			}// kalendár pre KALENDAR_SK_OP

			break;

		case 16: // MES_APR -- 16APR

			if (_global_jazyk == JAZYK_HU){
				if (poradie_svaty == 1){
					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						// _vlastna_cast_benediktus_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						// _vlastna_cast_magnifikat_spomprivileg; // TODO: treba doplniť antifónu zo spoločnej časti (do vlastnej časti) a odpoznámkovať tento kód, aby bolo správne zobrazené zakončenie
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie_spomprivileg;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						// _vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						// _vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_16[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
				break;
			}// HU only

			break;

		case 17: // MES_APR -- 17APR
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				else if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_APR_17_1_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty2.meno, text_APR_17_2_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
				break;
			}// kalendár pre KALENDAR_SK_OP

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie_spomprivileg;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_17_OCD[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				break;
			}// kalendár pre KALENDAR_SK_OCD

			break;

		case 18: // MES_APR -- 18APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat_spomprivileg;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie_spomprivileg;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_18_OCD[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				break;
			}// kalendár pre KALENDAR_SK_OCD

			break;

		case 19: // MES_APR -- 19APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				else if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// na spomienku v privilegovaný deň (spomienka v pôste)
					if (je_privileg){
						if (query_type != PRM_DETAILY)
							set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba_spomprivileg;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;

					}// je_privileg
					else{
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_modlitba;
					}// nie je pôst

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_APR_19_1_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty2.meno, text_APR_19_2_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
				break;
			}// kalendár pre KALENDAR_SK_OP

			break;

		case 20: // MES_APR -- 20APR

			if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
				if (poradie_svaty == 1){

					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
						file_name_vlastny_kalendar(_global_kalendar);
					}
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					if (_global_jazyk == JAZYK_CZ_OP){
						_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
					}
					else{
						_vlastna_cast_full_okrem_prosieb(modlitba);
					}

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 11; // miestne povinné spomienky
				if (_global_jazyk == JAZYK_CZ_OP){
					mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
					strcat(_global_svaty1.meno, text_APR_20_OP[_global_jazyk]);
					_global_svaty1.kalendar = KALENDAR_CZ_OP;
				}
				else
				{
					mystrcpy(_global_svaty1.meno, text_APR_20_OP[_global_jazyk], MENO_SVIATKU);
					_global_svaty1.kalendar = KALENDAR_SK_OP;
				}
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty1.farba = LIT_FARBA_BIELA;
			}// CZOP only, kalendár pre KALENDAR_SK_OP

			break;

		// 20APR/21APR: počnúc týmto dňom (21. apríla) LA LH, vol. II, p. 1401, neuvádza antifóny "pro commemoratione"

		case 21: // MES_APR -- 21APR

			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_21[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; // ľubovoľné spomienky
					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
						_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
					}
				}
				else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_global_svaty2.typslav = SLAV_SPOMIENKA;
					_global_svaty2.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				}

				pocet = 2;
				mystrcpy(_global_svaty2.meno, text_APR_21_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

			break;

		case 22: // MES_APR -- 22APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_ant_kcitresp_modl;
				}
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 8; // miestne sviatky
				mystrcpy(_global_svaty1.meno, text_APR_22_SJ[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SJ

			break;

		case 23: // MES_APR -- 23APR
			// vo všeobecnom kalendári sú 23. apríla sv. Juraj a sv. Vojtech

			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_HU)){
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_CZ))){
						_vlastna_cast_full_okrem_prosieb(modlitba);
					}
					else{
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;
					}

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;
					if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_CZ))){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}

					if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_CZ))){
						_vlastna_cast_mcd_kcitresp_modl;
					}

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
					if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_CZ))){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
						_vlastna_cast_kcitanie;
						_vlastna_cast_kresponz;
					}
					break;
				}
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
					_global_svaty1.typslav_lokal = LOKAL_SLAV_PRAHA_PATRON;
				}
				else{
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
				}
				mystrcpy(_global_svaty1.meno, text_APR_23[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
				}
				else if (_global_jazyk == JAZYK_HU){
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
				}
				else{ // if(_global_jazyk == JAZYK_SK)...
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
				}
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					pom_poradie = (_global_jazyk == JAZYK_HU)? 3 : 2;
					if (poradie_svaty == pom_poradie){

						file_name_vlastny_kalendar(_global_kalendar);

						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						if (_global_jazyk == JAZYK_HU){
							_vlastna_cast_magnifikat;
						}
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty(pom_poradie).typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty(pom_poradie).smer = 12; // ľubovoľné spomienky
					pocet = pom_poradie;
					mystrcpy(_global_svaty(pom_poradie).meno, text_APR_23_OFM[_global_jazyk], MENO_SVIATKU);
					if (_global_jazyk == JAZYK_HU){
						_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					}
					else{
						_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					}
					_global_svaty(pom_poradie).farba = LIT_FARBA_BIELA;
					_global_svaty(pom_poradie).kalendar = _global_kalendar;
				}// kalendár pre KALENDAR_SK_OFM
			}// SK, CZ, HU

			else{ // _global_jazyk nie je slovenčina ani čeština
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				else if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_24_1[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_APR_23[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY;
			}// nie SK, ani CZ, HU, CZOP

			if (_global_jazyk == JAZYK_HU){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_PRVE_VESPERY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_PRVE_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_ant_kcitresp_modl;

					// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
					if (_global_den.denvt != DEN_NEDELA) {
						_set_zalmy_mcd_doplnkova_psalmodia();
					}
					else {
						_set_zalmy_1nedele_mcd();
					}

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					break;
				}

				pocet = ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)) ? 3 : 2;
				_global_svaty2.typslav = SLAV_SLAVNOST;
				_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
				_global_svaty2.typslav_lokal = LOKAL_SLAV_ESZTERGOM_FOEGYH;
				mystrcpy(_global_svaty2.meno, text_APR_23_HU[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
			}// HU only

			break;

		case 24: // MES_APR -- 24APR

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);
					_set_zalmy_1nedele_rch();

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);
					_set_zalmy_sviatok_duch_past(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				mystrcpy(_global_svaty1.meno, text_APR_24_OPRAEM[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = KALENDAR_CZ_OPRAEM;
			}// kalendár pre KALENDAR_CZ_OPRAEM

			// vo všeobecnom kalendári sú 23. apríla sv. Juraj a sv. Vojtech
			else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
						// almost nothing special

						modlitba = MODL_RANNE_CHVALY;
						// _vlastna_cast_benediktus;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						// _vlastna_cast_2citanie;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						// _vlastna_cast_magnifikat;
						_vlastna_cast_modlitba;
					}// HU
					else{
						modlitba = MODL_INVITATORIUM;
						_vlastna_cast_antifona_inv;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_full_okrem_hymnu(modlitba);
						if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
							_vlastna_cast_hymnus(modlitba, _global_den.litobd);
						}
						_set_zalmy_sviatok_muc_ofm(modlitba);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full_okrem_hymnu(modlitba);
						if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
							_vlastna_cast_hymnus(modlitba, _global_den.litobd);
						}
						_set_zalmy_sviatok_muc_ofm(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full_okrem_hymnu(modlitba);
						if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
							_vlastna_cast_hymnus(modlitba, _global_den.litobd);
						}
						_set_zalmy_sviatok_muc_ofm(modlitba);

						_vlastna_cast_mcd_kcitresp_modl;
					}// SK, CZ

					break;
				}
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_global_svaty1.typslav = SLAV_SPOMIENKA;
					_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
						_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
					}
				}
				else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_global_svaty1.typslav = SLAV_SVIATOK;
					_global_svaty1.smer = 8; // miestne sviatky
				}
				mystrcpy(_global_svaty1.meno, text_APR_24_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

			else if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_HU)){
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				else if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_24_1[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
				}
				else if (_global_jazyk == JAZYK_HU){
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
				}
				else{ // if(_global_jazyk == JAZYK_SK)...
					_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_APR_24_2[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
					if (poradie_svaty == 3){

						file_name_vlastny_kalendar(_global_kalendar);

						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						_vlastna_cast_modlitba;

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;
						break;
					}

					pocet = 3;
					_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty3.smer = 12; // ľubovoľné spomienky
					mystrcpy(_global_svaty3.meno, text_APR_24_OCD[_global_jazyk], MENO_SVIATKU);
					_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
					_global_svaty3.farba = LIT_FARBA_BIELA;
					_global_svaty3.kalendar = _global_kalendar;
					break;
				}// kalendár pre KALENDAR_SK_OCD
			}// SK, CZ, HU

			else{
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_24_2[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
			}

			break;

		// 25APR // 25. apríl je najneskorší možný dátum veľkonočnej nedele

		case 25: // MES_APR -- 25APR

			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full_okrem_antifon(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_APR_25[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			break;

		case 26: // MES_APR -- 26APR

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				mystrcpy(_global_svaty1.meno, text_APR_26_OPRAEM[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_CZ_OPRAEM

			break;

		// 25APR/26APR: Veľká noc nepripadne po tomto dátume

		case 27: // MES_APR -- 27APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_27_SJ[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SJ

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty1.meno, text_APR_27_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;
				break;
			}// kalendár pre KALENDAR_SK_OP

			break;

		case 28: // MES_APR -- 28APR

			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_28_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_APR_28_2[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 3){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				pocet = 3;
				_global_svaty3.typslav = SLAV_SPOMIENKA;
				_global_svaty3.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty3.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty3.meno, text_APR_28_2[_global_jazyk]);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = KALENDAR_CZ_OP;
			}// CZOP only

			else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_APR_28_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_HU_OFM

			break;

		case 29: // MES_APR -- 29APR

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);
					// 2012-04-02: doplnené žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					set_zalm(1, modlitba, "z138.htm", "ZALM138_OP");
					set_zalm(2, modlitba, "z25.htm", "ZALM25_CELY");
					set_zalm(3, modlitba, "z67.htm", "ZALM67_OP");

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);
					_vlastna_cast_modlitba_ina; // Alebo ako na ranné chvály.
					// 2012-04-02: doplnené žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					set_zalm(1, modlitba, "z31.htm", "ZALM31,20-25");
					set_zalm(2, modlitba, "z84.htm", "ZALM84_OP");
					set_zalm(3, modlitba, "ch_zjv4_5.htm", "CHVAL_ZJV45");

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty1.meno, text_APR_29[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			else{
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					if (_global_jazyk != JAZYK_CZ){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					if (_global_jazyk != JAZYK_CZ){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					if (_global_jazyk != JAZYK_CZ){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					// _vlastna_cast_mcd_kcitresp_modl; // krátke čítanie a krátke resp. zo spoločnej časti
					_vlastna_cast_mcd_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty1.meno, text_APR_29[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

				if (_global_jazyk == JAZYK_CZ_OP){
					if (poradie_svaty == 2){
						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_INVITATORIUM;
						_vlastna_cast_antifona_inv;

						modlitba = MODL_RANNE_CHVALY;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_full(modlitba);

						modlitba = MODL_VESPERY;
						_vlastna_cast_full(modlitba);

						_vlastna_cast_mcd_kcitresp_modl;

						break;
					}

					pocet = 2;
					_global_svaty2.typslav = SLAV_SVIATOK;
					_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
					mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
					strcat(_global_svaty2.meno, text_APR_29[_global_jazyk]);
					_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
					_global_svaty2.farba = LIT_FARBA_BIELA;
					_global_svaty2.kalendar = KALENDAR_CZ_OP;
				}// CZOP only
			}// všeobecný kalendár

			break;

		case 30: // MES_APR -- 30APR
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_30[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			else if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_LA)){
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_30[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
					){
					if (poradie_svaty == 2){

						file_name_vlastny_kalendar(_global_kalendar);

						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;

						modlitba = MODL_RANNE_CHVALY;
						if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
							_vlastna_cast_benediktus;
						}
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
							_vlastna_cast_magnifikat;
						}
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; // ľubovoľné spomienky

					pocet = 2;
					mystrcpy(_global_svaty2.meno, text_APR_30_OFM[_global_jazyk], MENO_SVIATKU);
					_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					_global_svaty2.farba = LIT_FARBA_BIELA;
					_global_svaty2.kalendar = _global_kalendar;
				}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP
			}// SK, LA

			else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				// CZ, CZOP: okrem Pia V. majú aj sv. Žigmunda
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				else if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_APR_30_CZ[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_APR_30[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
					){
					if (poradie_svaty == 3){

						file_name_vlastny_kalendar(_global_kalendar);

						// definovanie parametrov pre modlitbu
						if (query_type != PRM_DETAILY)
							set_spolocna_cast(sc, poradie_svaty);

						modlitba = MODL_POSV_CITANIE;
						_vlastna_cast_2citanie;
						_vlastna_cast_modlitba;

						modlitba = MODL_RANNE_CHVALY;
						if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
							_vlastna_cast_benediktus;
						}
						_vlastna_cast_modlitba;

						modlitba = MODL_VESPERY;
						if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)) {
							_vlastna_cast_magnifikat;
						}
						_vlastna_cast_modlitba;

						break;
					}
					_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty3.smer = 12; // ľubovoľné spomienky

					pocet = 3;
					mystrcpy(_global_svaty3.meno, text_APR_30_OFM[_global_jazyk], MENO_SVIATKU);
					_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
					_global_svaty3.farba = LIT_FARBA_BIELA;
					_global_svaty3.kalendar = _global_kalendar;
				}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP
			}// CZ, CZOP only

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 3){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_SPOMIENKA;
				_global_svaty3.smer = 10; // povinné spomienky podľa všeobecného kalendára
				mystrcpy(_global_svaty3.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty3.meno, text_APR_30[_global_jazyk]);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = KALENDAR_CZ_OP;
			}// CZOP only

			break;
		};

		break; // case MES_APR
	}; // switch(mesiac - 1)

	return pocet;

}// sviatky_svatych_03_marec_04_april()

short int sviatky_svatych_05_maj(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_MAY;

	short int pom_poradie = 1;

	// premenné pom_den a pom_mesiac na uchovanie pôvodného dňa a mesiaca
	short int pom_den = den;
	short int pom_mesiac = mesiac;

	Log("mesiac máj\n");
	switch (den){

	case 1: // MES_MAY -- 01MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				// premenné pom_den a pom_mesiac na uchovanie pôvodného dňa a mesiaca pre český breviář sa totiž berú niektoré časti z 19. marca 
				pom_den = den;
				pom_mesiac = mesiac;
				den = 19;
				mesiac = MES_MAR + 1;

				sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac - 1]);
				Log("  _anchor_head == %s\n", _anchor_head);

				sprintf(_file, "sv_%s.htm", nazov_mes[mesiac - 1]);
				Log("  _file == %s\n", _file);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}
				else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
					_vlastna_cast_kresponz_po;
				}
				modlitba = MODL_VESPERY;
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}
				else if ((_global_den.litobd == OBD_POSTNE_I) || (_global_den.litobd == OBD_POSTNE_II_VELKY_TYZDEN)){
					_vlastna_cast_kresponz_po;
				}
			}// CZ, CZOP only
			else{
				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_kresponz;
				modlitba = MODL_VESPERY;
				_vlastna_cast_kresponz;
			}

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_kcitanie;
			_vlastna_cast_prosby;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_kcitanie;
			_vlastna_cast_prosby;

			if (_global_jazyk == JAZYK_CZ){
				// pre český breviář je aj hymnus na posv. čítanie z 19. marca

				sprintf(_file_pc, "pc_sv_%s.htm", nazov_mes[mesiac - 1]);
				Log("  _file_pc == %s\n", _file_pc);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				// premenné pom_den a pom_mesiac na uchovanie pôvodného dňa a mesiaca pre český breviář sa totiž berú niektoré časti z 19. marca | -- v tejto časti sa hodnoty upravujú späť na pôvodné --
				den = pom_den;
				mesiac = pom_mesiac;

				sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac - 1]);
				Log("  _anchor_head == %s\n", _anchor_head);

				sprintf(_file, "sv_%s.htm", nazov_mes[mesiac - 1]);
				Log("  _file == %s\n", _file);

				// kvôli zmene posv. čítania
				sprintf(_file_pc, "pc_sv_%s.htm", nazov_mes[mesiac - 1]);
				Log("  _file_pc == %s\n", _file_pc);
			}// CZ, CZOP only

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			if (_global_jazyk != JAZYK_CZ){
				// 2010-05-14: pre český breviář je aj hymnus na posv. čítanie z 19. marca
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_2citanie;
			_vlastna_cast_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAJ_01[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 2: // MES_MAY -- 02MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_MAJ_02[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_opraem_pc_1_8_24(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV;
			_global_svaty2.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty2.meno, text_MAJ_02_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 3: // MES_MAY -- 03MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_antifony;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			// 2010-05-03: český breviář má hymnus zo spol. časti
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_antifony;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_MAJ_03[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 4: // MES_MAY -- 04MAJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_04_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_04_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_04_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_04_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 5: // MES_MAY -- 05MAJ
		// pre dominikánov presunuté z 05APR (5.4.) zo všeobecného kalendára sv. Vincenta Ferrera...

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty1.meno, text_APR_05[_global_jazyk]);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_APR_05[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 6: // MES_MAY -- 06MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				// _vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				// antifóna na benediktus/magnifikat: vlastná sa berie iba na spomienku v pôstnom období
				_vlastna_cast_modlitba;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			if (_global_jazyk == JAZYK_SK) {
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SLAVNOST_SDB;
			}
			else {
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SLAVNOST_SDB_CZ;
			}
			mystrcpy(_global_svaty1.meno, text_MAJ_06_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_kcit_kresp_a_prosieb(modlitba);
				_set_zalmy_sviatok_muc(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_MAJ_06_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		} // CZ, CZOP only

		break;

	case 7: // MES_MAY -- 07MAJ

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_07_HU_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_VESZPREM_FOEGYH_T;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;

			pocet = 2;
			_global_svaty2.smer = 8; // miestne sviatky
			_global_svaty2.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty2.meno, text_MAJ_07_HU_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_EGER_FOEGYH2;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_07_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 8: // MES_MAY -- 08MAJ

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_kcitanie;
				_vlastna_cast_kresponz;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_kcitanie;
				_vlastna_cast_kresponz;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_08_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_08_3_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_08_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_08_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_MAJ_08_3_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_08_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 9: // MES_MAY -- 09MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			}
			mystrcpy(_global_svaty1.meno, text_MAJ_09_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		break;

	case 10: // MES_MAY -- 10MAJ

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				// 2009-07-10: doplnené invitatórium a niektoré časti z vlastnej časti
				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_MAJ_10_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_MAJ_10_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 11: // MES_MAY -- 11MAJ

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovolné spomienky podľa všeobecného kalendára -- Slovensko
			mystrcpy(_global_svaty1.meno, text_MAJ_11_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = (_global_jazyk == JAZYK_SK) ? KALENDAR_VSEOBECNY_SK : KALENDAR_VSEOBECNY_HU;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
				pocet = 2;
				mystrcpy(_global_svaty2.meno, text_MAJ_11_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 8; // miestne sviatky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_SVIATOK_OP_ZENY;
				mystrcpy(_global_svaty2.meno, text_MAJ_11_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP
		}// SK, HU only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_MAJ_11_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

// do 9. marca sú propriá vo zväzku III (cezročné obdobie), potom sa pokračuje až dňom 12. mája

	case 12: // MES_MAY -- 12MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if (poradie_svaty == 2){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if ((_global_jazyk == JAZYK_CZ) && (poradie_svaty == 3)){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY){
				set_spolocna_cast(sc, poradie_svaty);
			}
			// všetko je zo spoločnej časti na výročie posviacky chrámu

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAJ_12_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if (_global_jazyk == JAZYK_CZ){
			pocet = 3;
		}
		else{
			pocet = 2;
		}
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_MAJ_12_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty2.farba = LIT_FARBA_CERVENA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			_global_svaty3.smer = 11; // miestne povinné spomienky
			_global_svaty3.typslav_lokal = LOKAL_SLAV_PRAHA;
			_global_svaty3.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty3.meno, text_MAJ_12_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = KALENDAR_VSEOBECNY_CZ;
		}

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_MAJ_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 4){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 4;
			_global_svaty4.typslav = SLAV_SPOMIENKA;
			_global_svaty4.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty4.meno, text_MAJ_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty4.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty4.farba = LIT_FARBA_BIELA;
			_global_svaty4.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_MAJ_12_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 13: // MES_MAY -- 13MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				// nemá popis; 2013-02-04: doplnené
				set_popis_dummy();

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				// _vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SLAVNOST_FMA : LOKAL_SLAV_SLAVNOST_FMA_CZ;
			mystrcpy(_global_svaty1.meno, text_MAJ_13_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				// nemá popis; 2013-02-05: doplnené
				if (_global_jazyk != JAZYK_HU){
					set_popis_dummy();
				}

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_13[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_13_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_MAJ_11_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 14: // MES_MAY -- 14MAJ

		if (_global_jazyk != JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_benediktus;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_magnifikat;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_MAJ_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// v HU sa slávi 24FEB (24.2.)

		break;

	case 15: // MES_MAY -- 15MAJ

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty1.meno, text_MAJ_15_CZOP[_global_jazyk]);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_16_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_15_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_MAJ_15_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_MAJ_16_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 16: // MES_MAY -- 16MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_MAJ_16_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		else if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_HU)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_full_okrem_kcit_kresp_a_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full(modlitba);
					if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
						_vlastna_cast_kresponz_ve;
					}// inak zostane cezrocne, ale bez pripony
				}
				_set_zalmy_1nedele_rch(); // kvôli SK (CZ má sviatok, tam je to automaticky)

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				if (_global_jazyk == JAZYK_SK){
					_vlastna_cast_kresponz;
					// česká verzia má 1. čítanie zo spoločnej časti; vlastné prvé čítanie je len vtedy, ak sa slávi sviatok (vtedy sú aj antifóny a žalmy zo spoločnej časti jedného mučeníka a je aj hymnus Te Deum) | _vlastna_cast_1citanie;
				}

				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_vlastna_cast_mcd_modlitba;
				}

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_full_okrem_kcit_kresp_a_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full(modlitba);
					if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
						_vlastna_cast_kresponz_ve;
					}// inak zostane cezrocne, ale bez pripony
				}
				_set_zalmy_sviatok_muc(modlitba); // kvôli SK (CZ má sviatok, tam je to automaticky)

				break;
			}

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			}
			else if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
			}
			else {
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
				_global_svaty1.typslav_lokal = LOKAL_SLAV_ROZNAVA_PATRON;
			}// SK
			mystrcpy(_global_svaty1.meno, text_MAJ_16[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// SK, CZ, CZOP, HU only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_16_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_16_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 17: // MES_MAY -- 17MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){

			pom_poradie = (_global_jazyk == JAZYK_HU) ? 2 : 1;

			if (poradie_svaty == pom_poradie){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk != JAZYK_SK){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_SK){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk != JAZYK_SK){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			pocet = pom_poradie;
			_global_svaty(pom_poradie).typslav = SLAV_SPOMIENKA;
			_global_svaty(pom_poradie).smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty(pom_poradie).meno, text_MAJ_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty(pom_poradie).farba = LIT_FARBA_BIELA;
			_global_svaty(pom_poradie).kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_17_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZATMAR;
			break;
		}// HU only

		break;

	case 18: // MES_MAY -- 18MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk != JAZYK_HU){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk != JAZYK_HU){
					_vlastna_cast_full(modlitba);
					// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					_set_zalmy_pc_1_12_24(modlitba);
				}
				else{
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_HU){
					_vlastna_cast_full(modlitba);
					_set_zalmy_1nedele_rch();
				}
				else{
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;
				}

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_HU){
					_vlastna_cast_full(modlitba);
					// žalmy, ktoré sú len pre prvé vešpery sviatku duchovných pastierov, _set_zalmy_sviatok_duch_past()
					_set_zalmy_vesp_113_146_ef(modlitba);
				}
				else{
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 8; // miestne sviatky
			}
			else{
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
			}
			mystrcpy(_global_svaty1.meno, text_MAJ_18_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_18[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_MAJ_18_SDB[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB
		}// nie pre KALENDAR_SK_OFM

		break;

	case 19: // MES_MAY -- 19MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
			}
			else{
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_MAJ_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_19_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 20: // MES_MAY -- 20MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_vlastna_cast_1citanie;
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFM;
			}
			mystrcpy(_global_svaty1.meno, text_MAJ_20_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_MAR_15_CSSR[_global_jazyk], MENO_SVIATKU); // CZ CSsR: 20MAJ
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_CSSR

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			// pôvodne bola ľubovoľná spomienka na Sv. Klementa Marie Hofbauera - od 29.8.1991 památka pre Moravu; "v čechách si lidé mohou vybrat buď Klementa nebo Bernardina na Moravě máme předepsaného jenom Klementa." - p. Franta, 2008-05-21
			else if (poradie_svaty == 2){
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_MORAVA_SPOMIENKA;
			mystrcpy(_global_svaty1.meno, text_MAJ_20_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12;
			mystrcpy(_global_svaty2.meno, text_MAJ_20[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// CZ only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_20[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_MAJ_20_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 21: // MES_MAY -- 21MAJ

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_BRNO;
			_global_svaty1.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty1.meno, text_MAJ_21_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_MAJ_21_OP[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 3){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_MAJ_21[_global_jazyk], MENO_SVIATKU);
			// český breviár nemá možnosť pre duch. pastierov "pre viacerých"
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		else if (_global_jazyk == JAZYK_CZ){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_21[_global_jazyk], MENO_SVIATKU);
			// český breviár nemá možnosť pre duch. pastierov "pre viacerých"
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
					_vlastna_cast_2citanie; // 2011-02-09: doplnený pracovný preklad
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_21[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_21_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 22: // MES_MAY -- 22MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;
			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAJ_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_22_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 23: // MES_MAY -- 23MAJ

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovolné spomienky podľa všeobecného kalendára -- Slovensko
			mystrcpy(_global_svaty1.meno, text_MAJ_23_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 24: // MES_MAY -- 24MAJ

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full(modlitba);
				}
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full(modlitba);
				}
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_MAJ_24_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_MAJ_24_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_MAJ_24[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_MAJ_24[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){

			pom_poradie = (_global_jazyk == JAZYK_HU) ? 2 : 1;

			if (poradie_svaty == pom_poradie){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				// Všetko ostatné je zo spoločnej časti na výročie posviacky chrámu
				break;
			}

			pocet = pom_poradie;
			_global_svaty(pom_poradie).smer = 8; // miestne sviatky
			_global_svaty(pom_poradie).typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty(pom_poradie).meno, text_MAJ_24_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty(pom_poradie).farba = LIT_FARBA_BIELA;
			_global_svaty(pom_poradie).kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_MAJ_24_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 25: // MES_MAY -- 25MAJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_MAJ_25_3[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA /* MODL_SPOL_CAST_SV_ZENA_REHOLNIK */);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_25_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 3;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_25_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_MAJ_25_3[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 26: // MES_MAY -- 26MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_MAJ_26[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 27: // MES_MAY -- 27MAJ

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_MAJ_27[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_PLZEN;
			_global_svaty2.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty2.meno, text_DEC_02_CZ[_global_jazyk], MENO_SVIATKU); // presunuté z 2. decembra
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_MAJ_27_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 28: // MES_MAY -- 28MAJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_28_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_SK_OP;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_28_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 29: // MES_MAY -- 29MAJ

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_29_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_29_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_MAJ_29_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_MAJ_30_OP[_global_jazyk], MENO_SVIATKU); // SK OP slávia 30. mája sv. Zdislavu, ako CZ OP
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 30: // MES_MAY -- 30MAJ

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_30_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					_vlastna_cast_full_okrem_antifon(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd); // v českom breviári má vlastný hymnus; 2009-08-13 | aj SK OP má vlastný hymnus
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					_vlastna_cast_full_okrem_antifon(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_MAJ_30_CZ[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
			else{
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
				_global_svaty1.typslav_lokal = LOKAL_SLAV_CESKO_BRNO;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
			}
		}// CZ, CZOP only, kalendár pre KALENDAR_SK_OP

		if (_global_jazyk == JAZYK_CZ){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				_vlastna_cast_mcd_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.smer = 8; // miestne sviatky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_LITOMERICE;
			mystrcpy(_global_svaty2.meno, text_MAJ_30_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ only

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				_vlastna_cast_mcd_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_MAJ_30_CZ[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_MAJ_30_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM
		
		break;

	case 31: // MES_MAY -- 31MAJ

		// na Slovensku (aj v Maďarsku) sa slávi 2. júla
		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_MAJ_31[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// CZ, CZOP only

		break;
	};

	return pocet;
}// sviatky_svatych_05_maj()

short int sviatky_svatych_06_jun(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	short int pom_poradie = 1;

	Log("mesiac jún\n");
	switch (den){

	case 1: // MES_JUN -- 01JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUN_01[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 2: // MES_JUN -- 02JUN

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUN_02_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár KALENDAR_CZ_OFMCAP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_02[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_JUN_02_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty2.meno, text_JUN_02_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP
		}// všeobecný kalendár

		break;

	case 3: // MES_JUN -- 03JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUN_03[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 4: // MES_JUN -- 04JUN

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_JUN_04_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_JUN_04_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_04_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZOMBATHELYI_EGYH;
		}// HU only

		break;

	case 5: // MES_JUN -- 05JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_DEBR_NYIREGY;
		}
		mystrcpy(_global_svaty1.meno, text_JUN_05[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 6: // MES_JUN -- 06JUN

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				if ((_global_den.litobd == OBD_VELKONOCNE_I) || (_global_den.litobd == OBD_VELKONOCNE_II)){
					_vlastna_cast_kresponz_ve;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_opraem_pc_1_8_24(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// pre modlitbu cez deň na slávnosť sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_JUN_06_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // lubovolne spomienky podla vseobecneho kalendara
			mystrcpy(_global_svaty1.meno, text_JUN_06[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 7: // MES_JUN -- 07JUN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUN_07_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 8: // MES_JUN -- 08JUN

		if ((_global_jazyk == JAZYK_HU) && !(_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_08_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only except KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_JUN_08_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNY_VIACERE);
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_JUN_08_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNY_VIACERE, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_08_OFM[_global_jazyk], MENO_SVIATKU); // note: HU celebration is for another saint!
			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			}
			else{
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_08_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 9: // MES_JUN -- 09JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JUN_09[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // miestne ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUN_09_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 10: // MES_JUN -- 10JUN

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_JUN_10_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_JUN_10_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 11: // MES_JUN -- 11JUN

		if (poradie_svaty == 1){

			// LH uvádza: ako na sviatok sv. Marka 25APR okrem toho, čo nasleduje
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_antifon(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_kcitresp_modl;

			modlitba = MODL_VESPERY;
			_vlastna_cast_full_okrem_antifon(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUN_11[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 12: // MES_JUN -- 12JUN

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OSTRAVA_OPAVA;
			mystrcpy(_global_svaty1.meno, text_JUN_12_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			// CZ má ako poradie == 1 text_JUN_12_CZ
			pom_poradie = (_global_jazyk == JAZYK_CZ) ? 2 : 1;

			if (poradie_svaty == pom_poradie){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = pom_poradie;
			_global_svaty(pom_poradie).typslav = SLAV_SPOMIENKA;
			_global_svaty(pom_poradie).smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty(pom_poradie).meno, text_JUN_12_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty(pom_poradie).farba = LIT_FARBA_CERVENA;
			_global_svaty(pom_poradie).kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){

			short je_cz = (_global_jazyk == JAZYK_CZ) ? 1 : 0;

			if (poradie_svaty == 1 + je_cz){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2 + je_cz){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if ((poradie_svaty == 3) && ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty(1 + je_cz).typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty(1 + je_cz).smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty(1 + je_cz).meno, text_JUN_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(1 + je_cz).spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty(1 + je_cz).farba = LIT_FARBA_BIELA;
			_global_svaty(1 + je_cz).kalendar = _global_kalendar;

			_global_svaty(2 + je_cz).typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty(2 + je_cz).smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty(2 + je_cz).meno, text_JUN_12_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(2 + je_cz).spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty(2 + je_cz).farba = LIT_FARBA_BIELA;
			_global_svaty(2 + je_cz).kalendar = _global_kalendar;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				pocet = 3;
			}
			else{
				pocet = 2 + je_cz;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_JUN_12_3_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty3.farba = LIT_FARBA_CERVENA;
				_global_svaty3.kalendar = _global_kalendar;
			}
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JUN_12_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUN_12_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_SVD)) {
			if (poradie_svaty == 1) {

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_12_SVD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_SVD

		break;

	case 13: // MES_JUN -- 13JUN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){

			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty1.meno, text_JUN_13_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUN_13[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 8; // miestne sviatky
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_ORDINARIAT;
			mystrcpy(_global_svaty2.meno, text_JUN_13_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		break;

	case 14: // MES_JUN -- 14JUN

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZOMBATHELYI_EGYH;
			mystrcpy(_global_svaty1.meno, text_JUN_14_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_14_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 15: // MES_JUN -- 15JUN

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_PRAHA_KATEDRALA;
			mystrcpy(_global_svaty1.meno, text_JUN_15_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_HU) && !(_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_15_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_15_OFM_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 16: // MES_JUN -- 16JUN

		if (_global_jazyk == JAZYK_SK){
			// spomienka len v rožňavskej katedrále
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_ROZNAVA_KATEDRALA;
			mystrcpy(_global_svaty1.meno, text_JUN_16_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_panien(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_SVIATOK_SCSC;
			mystrcpy(_global_svaty2.meno, text_JUN_16_1_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_JUN_16_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				_set_zalmy_sviatok_duch_past(modlitba);

				break;
			}
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZOMBATHELYI_EGYH;
			mystrcpy(_global_svaty1.meno, text_JUN_16_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUN_16_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			// SK OFM: poradie 1 je text_JUN_16_SK; poradie 2 text_JUN_16_1_OFM; poradie 3 text_JUN_16_2_OFM
			// CZ OFMCap: poradie 1 je text_JUN_16_2_OFM
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_16_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 17: // MES_JUN -- 17JUN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 18: // MES_JUN -- 18JUN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JUN_18_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 19: // MES_JUN -- 19JUN

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_19[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// SK, HU only

		else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUN_19_CZ[_global_jazyk], MENO_SVIATKU); // CZ CSsR: 19JUN; SK CSsR: 05JAN (text_JAN_05_CSSR)
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_CSSR

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			// povinná spomienka len v čb-diecéze
			_global_svaty1.typslav_lokal = LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA;
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_19_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		break;

	case 20: // MES_JUN -- 20JUN

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OPRAEM_TEPLA;
			mystrcpy(_global_svaty1.meno, text_OPATSKY_KOSTOL_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 21: // MES_JUN -- 21JUN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa všeobecného kalendára -- 10 preto, lebo je to aj vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_JUN_21_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUN_21[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 22: // MES_JUN -- 22JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if (poradie_svaty == 2){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if ((_global_jazyk == JAZYK_HU) && (poradie_svaty == 3)){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY){
				set_spolocna_cast(sc, poradie_svaty);
			}
			// všetko je zo spoločnej časti na výročie posviacky chrámu

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_2citanie;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JUN_22_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		pocet = 2;
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_JUN_22_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty2.farba = LIT_FARBA_BIELA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		if (_global_jazyk == JAZYK_HU){

			pocet = 3;
			_global_svaty3.smer = 11; // miestne povinné spomienky
			_global_svaty3.typslav_lokal = LOKAL_SLAV_PECSI_EGYH;
			_global_svaty3.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty3.meno, text_JUN_22_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 23: // MES_JUN -- 23JUN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_23_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JUN_23_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 24: // MES_JUN -- 24JUN

		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// definovanie parametrov pre modlitbu
			if ((poradie_svaty == 1) &&
				(query_type != PRM_DETAILY))
				set_spolocna_cast(sc, poradie_svaty);

			if (_global_jazyk != JAZYK_CZ_OP){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_vlastna_cast_modlitba_ina;
			_set_zalmy_sviatok_sv_muzov(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_sv_muzov(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_sv_muzov(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		if (_global_jazyk == JAZYK_SK){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_TRNAVA_PATRON;
		}
		else if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_NAGYSZ_PATRON;
		}
		mystrcpy(_global_svaty1.meno, text_JUN_24[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 26: // MES_JUN -- 26JUN

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_26_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_26_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_27[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// HU only

		break;

	case 27: // MES_JUN -- 27JUN

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_JUN_27_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;
				_set_zalmy_sviatok_sv_muzov(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_sv_muzov(modlitba);

				break;
			}
			/* možno časom dorobiť slávnosť pre jednu diecézu
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätych, uvedené vo všeobecnom kalendári
			*/
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZ_LASZLO;
			mystrcpy(_global_svaty1.meno, text_JUN_27_SK_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// HU only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUN_27[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_SK){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				// v trnavskej, banskobystrickej, roznavskej a nitrianskej dieceze
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_TT_BB_NR_RO; // 2005-07-27: pridané; 2006-02-03: opravené, KE nie
				mystrcpy(_global_svaty2.meno, text_JUN_27_SK_HU[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY_SK;
			}// SK only
		}// všeobecný kalendár

		break;

	case 28: // MES_JUN -- 28JUN

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;
			// nema vespery, lebo su 1. vespery zo sv. petra a pavla

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUN_28[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 29: // MES_JUN -- 29JUN

		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("29JUN | Peter a Pavol: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if (_global_jazyk != JAZYK_CZ_OP){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_vlastna_cast_modlitba_ina;
			_set_zalmy_sviatok_apostolov(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			if (den != DEN_NEDELA){
				_set_kompletorium_slavnost(modlitba);
			}
			else{
				_set_kompletorium_nedela(modlitba);
			}

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_apostolov(modlitba);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_apostolov(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_apostolov(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			if (den != DEN_NEDELA){
				_set_kompletorium_slavnost(modlitba);
			}
			else{
				_set_kompletorium_nedela(modlitba);
			}

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		_global_svaty1.prik = PRIKAZANY_SVIATOK;
		mystrcpy(_global_svaty1.meno, text_JUN_29[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_PECSI_EGYH_PATRON;
		}

		break;

	case 30: // MES_JUN -- 30JUN

		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JUN_30[_global_jazyk], MENO_SVIATKU);

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_OLOMOUC;
			mystrcpy(_global_svaty2.meno, text_JUN_30_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUN_30_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUN_30_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_JUN_30_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_CSSR

		break;
	};

	return pocet;
}// sviatky_svatych_06_jun()

short int sviatky_svatych_07_jul(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	Log("mesiac júl\n");
	switch (den){

	case 1: // MES_JUL -- 01JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_02_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 2: // MES_JUL -- 02JUL

		// vo všeobecnom kalendári sa slávi 31. mája
		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				// nemá popis; 2013-02-04: doplnené
				if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
					set_popis_dummy();
				}

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_mcd_kcitresp_modl;
				}
				else{
					_vlastna_cast_mcd_modlitba;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_MAJ_31[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_SK){
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
			}
			else if (_global_jazyk == JAZYK_HU){
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			}
		}// SK, HU only

		break;

	case 3: // MES_JUL -- 03JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastna_cast_antifony;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;
			}
			else{
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				// 2008-10-15: odvetvené len pre Česko
				// 2008-11-29: pridané czop - dominikánský breviář
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_antifony_ako_na_ranne_chvaly;
			if (!((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP))){
				_vlastna_cast_kcitanie;
				_vlastna_cast_kresponz;
			}
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_JUL_03[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 4: // MES_JUL -- 04JUL

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_LA)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				if (_global_jazyk != JAZYK_SK){
					// SK nemá vešpery, lebo sú 1. vešpery zo sv. cyrila a metoda
					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;
				}
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_04[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL, MODL_SPOL_CAST_SV_ZENA_MANZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// SK, HU, LA only

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_CECHY_SPOMIENKA;
			mystrcpy(_global_svaty1.meno, text_JUL_04_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_04[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL, MODL_SPOL_CAST_SV_ZENA_MANZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JUL_04_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_JUL_04_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 5: // MES_JUL -- 05JUL

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
			_global_opt[OPT_3_SPOLOCNA_CAST] = _decode_spol_cast(_global_svaty1.spolcast).a1;
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_den.typslav = SLAV_SLAVNOST; // doplnené kvôli správnemu fungovaniu set_spolocna_cast(), t. j. tamojších kontrol, či napr. sú žalmy vlastné
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_JUL_05[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ, CZOP only
			else
			{
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
			}// SK only

			if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){

				// definovanie parametrov pre modlitbu
				sc = _decode_spol_cast(_global_svaty1.spolcast);
				Log("05JUL | Cyril a Metod: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				// slovenský breviár má iné žalmy
				if (_global_jazyk == JAZYK_SK){
					_set_zalmy_slavnost_Cyrila_a_Metoda(modlitba);
				}
				else{
					_set_zalmy_sviatok_duch_past(modlitba);
				}
				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ)){
					_vlastna_cast_full(modlitba);
				}
				else{
					// pre CZOP sú antifóny a krátky responz pred 1. čítaním zo spoločnej časti
					_vlastna_cast_1citanie;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;
				}
				// slovenský breviár má iné žalmy
				if (_global_jazyk == JAZYK_SK){
					_set_zalmy_slavnost_Cyrila_a_Metoda(modlitba);
				}
				else{
					_set_zalmy_sviatok_duch_past(modlitba);
				}
				// hymnus ako na vešpery
				_set_hymnus_alternativy_NO(modlitba, _global_den.litobd); // 2013-07-31: doplnené, nakoľko bolo doplnené do _vlastna_cast_hymnus_ako_na_vespery() a _vlastna_cast_hymnus()
				// kedysi: pre CZ a CZOP hymnus ako na 1. vešpery | teraz použitý hymnus z 1. vešpier len pre CZOP; pre CZ použitý hymnus zo sv. III, str. 1462
				if (_global_jazyk != JAZYK_CZ){
					sprintf(_anchor, "%s%c%s", _anchor_head, pismenko_modlitby((_global_jazyk == JAZYK_SK) ? MODL_VESPERY : /* _global_jazyk == JAZYK_CZ_OP */ MODL_PRVE_VESPERY), ANCHOR_HYMNUS);
					_set_hymnus(modlitba, _file, _anchor);
					set_LOG_svsv;
				}

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else{
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				// slovenský breviár má iné žalmy
				if (_global_jazyk == JAZYK_SK){
					_set_zalmy_slavnost_Cyrila_a_Metoda(modlitba);
				}
				else{
					_set_zalmy_sviatok_duch_past(modlitba);
				}
				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
					break;
				}
			}
		}// SK, CZ, CZOP only

		else if ((_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_LA)){
			// vo všeobecnom kalendári sa slávi; presunuté na SK na 7. júla
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_07_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// HU, LA only

		break;

	case 6: // MES_JUL -- 06JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JUL_06[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (_global_jazyk == JAZYK_CZ_OP){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_JUL_06_CZOP[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// CZOP only

		break;

	case 7: // MES_JUL -- 07JUL

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SPOMIENKA_FMA : LOKAL_SLAV_SPOMIENKA_FMA_CZ;
			mystrcpy(_global_svaty1.meno, text_JUL_07_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_SDB a KALENDAR_CZ_SDB

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_07_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_VYCH, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_FMA;
			mystrcpy(_global_svaty2.meno, text_JUL_07_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JUL_07_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 8: // MES_JUL -- 08JUL

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZEGED_CSAN_EGYH;
			mystrcpy(_global_svaty1.meno, text_JUL_08_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_08_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JUL_08_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_SV_MUZ_MANZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 9: // MES_JUL -- 09JUL

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUL_09_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_CZ_OPRAEM;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_09[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){

				pocet = 2;

				if (poradie_svaty == 2){

					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
						file_name_vlastny_kalendar(_global_kalendar);
					}
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					if (_global_jazyk == JAZYK_CZ_OP){
						_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
					}
					else{
						_vlastna_cast_full_okrem_prosieb(modlitba);
					}

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					if (_global_jazyk == JAZYK_CZ_OP){
						_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
					}
					else{
						_vlastna_cast_full_okrem_prosieb(modlitba);
					}

					break;
				}
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 11; // miestne povinné spomienky
				if (_global_jazyk == JAZYK_CZ_OP){
					mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
					strcat(_global_svaty2.meno, text_JUL_09_OP[_global_jazyk]);
					_global_svaty2.kalendar = KALENDAR_CZ_OP;
				}
				else
				{
					mystrcpy(_global_svaty2.meno, text_JUL_09_OP[_global_jazyk], MENO_SVIATKU);
					_global_svaty2.kalendar = KALENDAR_SK_OP;
				}
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
			}// CZOP only, kalendár pre KALENDAR_SK_OP

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){

				pocet = 2;
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				if (_global_jazyk == JAZYK_HU){
					_global_svaty2.typslav = SLAV_SPOMIENKA;
					_global_svaty2.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				}
				else{
					_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
					_global_svaty2.smer = 12; // ľubovoľné spomienky
					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
						_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
					}
				}
				mystrcpy(_global_svaty2.meno, text_JUL_09_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM
		}// všeobecný kalendár a špecifické prípady odlišné od OPRAEM

		break;

	case 10: // MES_JUL -- 10JUL

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;
				}// KALENDAR_CZ_OFMCAP
				else{
					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// KALENDAR_SK_OFM
				break;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
			}
			else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 8; // miestne sviatky
			}
			else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_JUL_10_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 11: // MES_JUL -- 11JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_benediktus
				if (_global_jazyk == JAZYK_SK){
					_vlastna_cast_prosby;
				}// české má zo spoločnej časti: o sv. mužích nebo o řeholnících
			if (_global_jazyk == JAZYK_CZ_OP){
				_vlastna_cast_kresponz;
			}// české CZOP má v spoločnej časti: o sv. mužích odlišné ako vo vlastnej časti...
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd); // hymnus ako na vešpery
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_magnifikat;
			if (_global_jazyk == JAZYK_HU){
				_vlastna_cast_kresponz;
			}
			else if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_kresponz;
				_vlastna_cast_prosby;
			}
			// české má zo spoločnej časti: o sv. mužích nebo o řeholnících; to isté aj krátke responzórium
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_JUL_11[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 12: // MES_JUL -- 12JUL

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_12_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_MANZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 13: // MES_JUL -- 13JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUL_13_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_13[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				pocet = 2;
				mystrcpy(_global_svaty2.meno, text_JUL_13_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				mystrcpy(_global_svaty2.meno, text_JUL_13_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_HU_OFM
		}// všeobecný kalendár

		break;

	case 14: // MES_JUL -- 14JUL

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUL_14_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					if (je_CZ_hymny_k_volnemu_vyberu){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					if (je_CZ_hymny_k_volnemu_vyberu){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					if (je_CZ_hymny_k_volnemu_vyberu){
						_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					}
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_PLZEN_PATRON;
				mystrcpy(_global_svaty2.meno, text_JUL_14_CZ[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ, CZOP only

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){
				pocet = 2;
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_JUL_14_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){

				pocet = 3;

				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_JUL_14_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_CZ_OFMCAP
		}// všeobecný kalendár

		break;

	case 15: // MES_JUL -- 15JUL

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_JUL_15_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUL_15[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 16: // MES_JUL -- 16JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// pre modlitbu cez deň na slávnosť sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_JUL_16_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA); // kvôli psalmódii
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_set_zalmy_sviatok_marie(modlitba);
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_16[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY){
						set_spolocna_cast(sc, poradie_svaty);
					}
					// všetko je zo spoločnej časti na výročie posviacky chrámu

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 8; // miestne sviatky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_OSTRAVA_OPAVA;
				mystrcpy(_global_svaty2.meno, text_JUL_16_CZ[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ, CZOP only
		}// všeobecný kalendár

		break;

	case 17: // MES_JUL -- 17JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_HYMNUS); // HYMNUS Vypočuj prosby, Ježišu, ako je uvedený v spoločnej časti na sviatky panien

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUL_17_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNY_VIACERE, MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else if (_global_jazyk == JAZYK_SK){
			// v Nitrianskej dieceze sviatok - hlavni patroni
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			_global_svaty1.typslav_lokal = LOKAL_SLAV_NITRA_PATRON;
			mystrcpy(_global_svaty1.meno, text_JUL_17_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_17_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_benediktus;
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_17_CZ[_global_jazyk], MENO_SVIATKU);
			// český breviár nemá možnosť pre duch. pastierov "pre viacerých"
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_JUL_17_OP[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// CZ, CZOP only

		break;

	case 18: // MES_JUL -- 18JUL

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUL_18_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_18_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_17_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JUL_18_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 19: // MES_JUL -- 19JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_JUL_19_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 20: // MES_JUL -- 20JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ocd_elias(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ocd_elias(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ocd_elias(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_JUL_20_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_20[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 21: // MES_JUL -- 21JUL
		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// hu only
				else{
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);
					// 2013-08-18: doplnené žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité (bežne pre nedeľu 3. týždňa žaltára)
					_set_zalmy_pc_145(modlitba);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);
					_set_zalmy_1nedele_rch();

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);
					_set_zalmy_sviatok_krstu(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;
				}
				break;
			}
			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
				){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
				}
			}
			else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 8; // miestne sviatky
			}
			mystrcpy(_global_svaty1.meno, text_JUL_21_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_21[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 22: // MES_JUL -- 22JUL
		if (poradie_svaty == 1){

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				file_name_vlastny_kalendar(_global_kalendar);
			}// pre KALENDAR_SK_OP

			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			_set_zalmy_1nedele_rch();
			_vlastna_cast_kresponz;
			_vlastna_cast_kcitanie; // má byť rovnaké ako zo spoločnej časti svätých žien
			_vlastna_cast_benediktus;
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				_vlastna_cast_prosby;
			}
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			// žalmy zo spoločnej časti sv. žien
			_set_zalmy_sviatok_panien(modlitba);
			_vlastna_cast_kresponz;
			_vlastna_cast_kcitanie; // má byť rovnaké ako zo spoločnej časti svätých žien
			_vlastna_cast_magnifikat;
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				_vlastna_cast_prosby;
			}
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUL_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			_global_svaty1.kalendar = _global_kalendar;
		}// pre KALENDAR_SK_OP

		break;

	case 23: // MES_JUL -- 23JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUL_23[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 24: // MES_JUL -- 24JUL

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUL_24_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_24[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_24_OFM[_global_jazyk], MENO_SVIATKU);
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			}
			else{
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			}// HU
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_JUL_24_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_JUL_24_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_24_1_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_PANNY_VIACERE);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_JUL_24_2_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 25: // MES_JUL -- 25JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			_vlastna_cast_kcitanie;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_antifony;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_JUL_25[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 26: // MES_JUL -- 26JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			else{
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUL_26[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_MANZ, MODL_SPOL_CAST_SV_ZENA_MANZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_VESZPREMI_EGYH_PATRON;
		}
		break;

	case 27: // MES_JUL -- 27JUL

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_vlastna_cast_benediktus;
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
					_vlastna_cast_magnifikat;
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára

			// kedysi pre CZ: _global_svaty1.typslav_lokal = LOKAL_SLAV_MORAVA_SPOMIENKA;

			mystrcpy(_global_svaty1.meno, text_JUL_27[_global_jazyk], MENO_SVIATKU);
			if (_global_jazyk == JAZYK_SK){
				// slovenský breviár má: zo spol. časti svätých mužov
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
			}
			else{
				// český breviář má: spol. texty o duchovních pastýřech; český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
			}
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// SK, CZ only

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_24[_global_jazyk], MENO_SVIATKU); // HU: 27JUL
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// HU only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_27_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_JUL_27_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 28: // MES_JUL -- 28JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_JUL_27_OP[_global_jazyk], MENO_SVIATKU); // SK OP: 28JUL
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_28_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_MUCENICA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_28_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_JUL_27_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 29: // MES_JUL -- 29JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
			}
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_JUL_29[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 30: // MES_JUL -- 30JUL

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_JUL_30[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		// Sviatok Bl. Zdenky Schelingovej, panny a mučenice, ako 2. možnosť | upozornil Jan Kusenda <exonkuda@savba.sk>
		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 2){

				if (_global_kalendar == KALENDAR_SK_OFM){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // lubovolne spomienky podla vseobecneho kalendara - Slovensko
			if (_global_kalendar == KALENDAR_SK_OFM){
				_global_svaty2.typslav_lokal = LOKAL_SLAV_SVIATOK_SCSC;
				mystrcpy(_global_svaty2.meno, text_JUL_30_SK_OFM[_global_jazyk], MENO_SVIATKU);
			}
			else{
				_global_svaty2.typslav_lokal = LOKAL_SLAV_KONGREGACIA_SSK;
				mystrcpy(_global_svaty2.meno, text_JUL_30_SK[_global_jazyk], MENO_SVIATKU);
			}
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			if (_global_kalendar == KALENDAR_SK_OFM){
				_global_svaty2.kalendar = KALENDAR_SK_OFM;
			}
			else{
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY_SK;
			}
		}// SK only

		break;

	case 31: // MES_JUL -- 31JUL

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sj_ignac(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sj_ignac(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sj_ignac(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sj_ignac(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_JUL_31_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_JUL_31[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;
	};

	return pocet;
}// sviatky_svatych_07_jul()

short int sviatky_svatych_08_august(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	Log("mesiac august\n");
	switch (den){

	case 1: // MES_AUG -- 01AUG

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_antifony;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// pre modlitbu cez deň na slávnosť sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_prosby;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_01_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_01[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 2: // MES_AUG -- 02AUG

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					modlitba = MODL_PRVE_VESPERY;
					_vlastna_cast_full(modlitba);

					// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
					if (_global_den.denvt != DEN_NEDELA) {
						_set_zalmy_mcd_doplnkova_psalmodia();
					}
					else {
						_set_zalmy_1nedele_mcd();
					}
				}

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_marie(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_marie(modlitba);
				_vlastna_cast_full(modlitba);

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_mcd_ant_kcitresp_modl;
				}// KALENDAR_CZ_OFMCAP
				else{
					_vlastna_cast_mcd_kcitresp_modl;
				}

				break;
			}
			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SLAVNOST;
				_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			}
			else{
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			}// KALENDAR_SK_OFM, KALENDAR_HU_OFM
			mystrcpy(_global_svaty1.meno, text_AUG_02_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			pocet = 2;
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			else if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
				if (poradie_svaty == 3){

					if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
						file_name_vlastny_kalendar(_global_kalendar);
					}
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				if (_global_jazyk == JAZYK_CZ_OP){
					mystrcpy(_global_svaty3.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
					strcat(_global_svaty3.meno, text_AUG_02_OP[_global_jazyk]);
					_global_svaty3.kalendar = KALENDAR_CZ_OP;
				}
				else
				{
					mystrcpy(_global_svaty3.meno, text_AUG_02_OP[_global_jazyk], MENO_SVIATKU);
					_global_svaty3.kalendar = KALENDAR_SK_OP;
				}
			}// CZOP only, kalendár pre KALENDAR_SK_OP

			else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					// _vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_AUG_02_SDB[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

			else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_AUG_02_SJ[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SJ

			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_02_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_02_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 3: // MES_AUG -- 03AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_AUG_03_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 4: // MES_AUG -- 04AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_AUG_04[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 5: // MES_AUG -- 05AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_AUG_05[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 6: // MES_AUG -- 06AUG

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o sviatok Pana, ktora ma velku prioritu, a preto ma aj - ak je nedela - prve vespery 

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("06AUG | Premenenie Pana: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			// nemá popis
			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_premenenie(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastna_cast_mcd_full;
			}
			else{
				// žalmy sú z bežného dňa (LH, zv. IV, str. 1306)
				_vlastna_cast_mcd_ant_kcitresp_modl;
			}

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_premenenie(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_premenenie(modlitba);

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_premenenie(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			// ak padne tento sviatok na sobotu, kompletórium (po druhých vešperách) má byť nedeľné, po prvých vešperách
			if (_global_den.denvt == DEN_SOBOTA){
				zaltar_kompletorium(DEN_NEDELA /* _global_den.denvt */, _global_den.litobd /* OBD_CEZ_ROK */, ZALTAR_VSETKO /* specialne */, _global_den.tyzzal);
				_global_modl_kompletorium = _global_modl_prve_kompletorium;
			}// DEN_SOBOTA
			else{
				zaltar_kompletorium(_global_den.denvt, _global_den.litobd /* OBD_CEZ_ROK */, ZALTAR_VSETKO /* specialne */, _global_den.tyzzal);
			}// iný deň ako sobota

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 5; // sviatky Pána uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_AUG_06[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 7: // MES_AUG -- 07AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_AUG_07_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if ((_global_jazyk == JAZYK_CZ_OP) && (poradie_svaty == 3)){
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}// CZOP only

			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_07_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_07_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_AUG_07_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty3.farba = LIT_FARBA_CERVENA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP
		}// všeobecný kalendár

		break;

	case 8: // MES_AUG -- 08AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_op_dominik(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_op_dominik(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_op_dominik(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				modlitba = MODL_PREDPOLUDNIM;
				_set_zalmy_op_dominik(modlitba);
				modlitba = MODL_NAPOLUDNIE;
				_set_zalmy_op_dominik(modlitba);
				modlitba = MODL_POPOLUDNI;
				_set_zalmy_op_dominik(modlitba);
				/*
				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if(_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
				_set_zalmy_1nedele_mcd();
				}
				*/
				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_op_dominik(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_08_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_set_zalmy_op_dominik(modlitba);
				}// KALENDAR_SK_OFM, KALENDAR_HU_OFM
				else{
					_set_zalmy_ofmcap_dominik(modlitba);
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_set_zalmy_op_dominik(modlitba);
				}// KALENDAR_SK_OFM, KALENDAR_HU_OFM
				else{
					_set_zalmy_ofmcap_dominik(modlitba);
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_full(modlitba);

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_vlastna_cast_mcd_ant_kcitresp_modl;
				}
				else{
					_vlastna_cast_mcd_kcitresp_modl;
				}// KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_AUG_08_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){

			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_AUG_08_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_08[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_PRVE_VESPERY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_PRVE_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_ant_kcitresp_modl;

					// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
					if (_global_den.denvt != DEN_NEDELA) {
						_set_zalmy_mcd_doplnkova_psalmodia();
					}
					else {
						_set_zalmy_1nedele_mcd();
					}

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SLAVNOST;
				_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_AUG_08[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 9: // MES_AUG -- 09AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_AUG_09_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_09[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK, MODL_SPOL_CAST_MUCENICA);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 10: // MES_AUG -- 10AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // v slovenskom breviári má vlastný hymnus, v českom nie
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}

			modlitba = MODL_POSV_CITANIE;
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // v slovenskom breviári má vlastný hymnus, v českom nie
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;
			_vlastna_cast_1citanie;
			_vlastna_cast_2citanie;
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // v slovenskom breviári má vlastný hymnus, v českom nie
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
			}

			// _vlastna_cast_mcd_kcitresp_modl; // modlitba cez deň: krátke čítanie a krátke resp. zo spoločnej časti
			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // v slovenskom breviári má vlastný hymnus, v českom nie
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_AUG_10[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 11: // MES_AUG -- 11AUG

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_panien(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
					|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
					){
					_set_zalmy_sviatok_panien(modlitba);
				}// KALENDAR_SK_OFM, KALENDAR_HU_OFM
				else{
					_set_zalmy_vesp_113_146_ef(modlitba);
				}// KALENDAR_CZ_OFMCAP

				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl; // Antifóny a žalmy sú z bežného dňa. Krátke čítanie je zo spoločnej časti na sviatky panien. Modlitba ako na ranné chvály.

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SLAVNOST_OSC;
			}// KALENDAR_SK_OFM
			else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_HU_KLARISSZAKNAL_FOU;
			}
			mystrcpy(_global_svaty1.meno, text_AUG_11_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_11[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 12: // MES_AUG -- 12AUG

		// Sviatok Sv. Jany Františky de Chantal presunuty z 12. decembra na 12. augusta.
		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_AUG_12[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK, MODL_SPOL_CAST_SV_ZENA_MANZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 4){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_AUG_12_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_AUG_12_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;

			pocet = 4;
			_global_svaty4.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty4.smer = 12; // ľubovoľné spomienky
			_global_svaty4.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty4.meno, text_AUG_12_3_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty4.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_MUCENIK);
			_global_svaty4.farba = LIT_FARBA_CERVENA;
			_global_svaty4.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 13: // MES_AUG -- 13AUG

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_AUG_13_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty1.meno, text_AUG_13_HU[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.farba = LIT_FARBA_BIELA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			}// HU only
			else{
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty1.meno, text_AUG_13[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
				// 2010-11-22: český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
				if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
					_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
				}
				else{
					_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
				}
			}// všeobecný kalendár

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_AUG_13_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP
		}// všeobecný kalendár a špecifické prípady odlišné od OPRAEM

		break;

	case 14: // MES_AUG -- 14AUG

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_benediktus;
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				// nema vespery, lebo su prve vespery nanebovzatia p. marie
				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCONV;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty1.meno, text_AUG_14_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				// nema vespery, lebo su prve vespery nanebovzatia p. marie
				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 15: // MES_AUG -- 15AUG

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o sviatok Pana, ktora ma velku prioritu, a preto ma aj - ak je nedela - prve vespery 

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("15AUG | Nanebovzatie prebl. Panny Márie: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_vlastna_cast_modlitba_ina;
			_set_zalmy_sviatok_panien(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_marie(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_panien(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_GYORI_SZEKESFEH_EGYH;
		}
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		_global_svaty1.prik = PRIKAZANY_SVIATOK;
		mystrcpy(_global_svaty1.meno, text_AUG_15[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 16: // MES_AUG -- 16AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_2citanie;
			_vlastna_cast_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		// [ToDo] 2011-07-21: Preveriť, či presun 13. a 16. augusta je len záležitosťou JAZYK_HU; slovenské direktórium na rok 2011 to neobsahuje
		if (_global_jazyk == JAZYK_HU){
			mystrcpy(_global_svaty1.meno, text_AUG_13[_global_jazyk], MENO_SVIATKU); // presun zo všeobecného kalendára
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only
		else{
			mystrcpy(_global_svaty1.meno, text_AUG_16[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_MANZ); // 2006-08-07: upravené lebo žil v manželstve :)
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			// 2013-12-11, e-mail od Mareka OPraem: památka sv. Rocha (16. srpna): texty ze Společných textů o svatých mužích: o svatých, kteří vynikali milosrdnými skutky. (Pozn.: V našem „propriu“, čili v té A5 červené knize, je odkaz na tyto společné texty; vlastní je pouze modlitba – ta se však může vzít ze společných textů…).
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_modlitba;
				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_STRAHOV;
			mystrcpy(_global_svaty2.meno, text_AUG_16_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_16_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 17: // MES_AUG -- 17AUG

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_AUG_17_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_AUG_17_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM; // ToDo: ešte pridať: "Slávnosť pre koncepcionistky"
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KAPORSVAR_FELSZ;
			mystrcpy(_global_svaty1.meno, text_AUG_17_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 18: // MES_AUG -- 18AUG

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_AUG_18_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_AUG_18_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_18_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_18_1_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_18_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_18_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_18_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
			break;
		}// kalendár pre KALENDAR_SK_OCD

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_VACI_FELSZ;
			mystrcpy(_global_svaty1.meno, text_AUG_18_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_19[_global_jazyk], MENO_SVIATKU); // HU 18AUG
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 19: // MES_AUG -- 19AUG

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_20[_global_jazyk], MENO_SVIATKU); // HU 19AUG
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_19[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
				mystrcpy(_global_svaty2.meno, text_AUG_19_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP
		} // excluding HU

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 20: // MES_AUG -- 20AUG

		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
			_global_opt[OPT_3_SPOLOCNA_CAST] = _decode_spol_cast(_global_svaty1.spolcast).a1;
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_den.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KAL_KECS_FOEGYH;
			mystrcpy(_global_svaty1.meno, text_AUG_16[_global_jazyk], MENO_SVIATKU); // HU 20AUG
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
				// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o slavnost, ktora ma takmer najvacsiu prioritu, a preto ma aj prve vespery - a vtedy by to normalne nefungovalo; nastavenie veci pre modlitbu by sa muselo diat v predoslom dni, co je neciste riesenie

				// definovanie parametrov pre modlitbu
				sc = _decode_spol_cast(_global_svaty1.spolcast);
				Log("20AUG | HU: Sv. Štefan: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_sv_muzov(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				// žalmy vlastné, ktoré zatiaľ nikde inde nie sú v tomto radení použité
				set_zalm(1, modlitba, "z21.htm", "ZALM21");
				set_zalm(2, modlitba, "z47.htm", "ZALM47");
				set_zalm(3, modlitba, "z61.htm", "ZALM61");

				_vlastna_cast_mcd_ant_kcitresp_modl;
				// modlitba cez deň na slávnosť: žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_sv_muzov(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
					break;
				}
			}
		}// HU only

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)) // v slovenskom breviári má vlastný hymnus, v českom nie; 2008-09-09; v dominikánskom áno; 2009-07-09
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)) // v slovenskom breviári má vlastný hymnus, v českom nie; 2008-09-09; v dominikánskom áno; 2009-07-09
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_20[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		} // všeobecný kalendár, excluding HU

		break;

	case 21: // MES_AUG -- 21AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_AUG_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 2){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SLAVNOST;
			_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_STRAHOV;
			mystrcpy(_global_svaty2.meno, text_OPATSKY_KOSTOL_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 22: // MES_AUG -- 22AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_AUG_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 23: // MES_AUG -- 23AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
				_vlastna_cast_modlitba_ina;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_23[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_SK_OP;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_23[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
				|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
				){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
						_vlastna_cast_prosby;
					}// KALENDAR_CZ_OFMCAP
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
						_vlastna_cast_prosby;
					}// KALENDAR_CZ_OFMCAP
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_AUG_23_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_kresponz;
					_vlastna_cast_kcitanie;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 11; // miestne povinné spomienky
				// 2009-07-10: odvetvené pre dominikánov
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_AUG_23[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár a špeciality

		break;

	case 24: // MES_AUG -- 24AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_AUG_24[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;
	
	case 25: // MES_AUG -- 25AUG

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk != JAZYK_SK){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}// KALENDAR_CZ_OFMCAP + KALENDAR_HU_OFM

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_full_okrem_antifon(modlitba);
				}// KALENDAR_CZ_OFMCAP
				else{
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// KALENDAR_SK_OFM

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFS;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty1.meno, text_AUG_25_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			else if (_global_jazyk == JAZYK_CZ){
				if (poradie_svaty == 3){

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}
				else if (poradie_svaty == 4){

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					break;
				}
			}// CZ only

			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_25_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VYCH, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){ // 2010-08-03: pridané aj CZOP
				pocet = 4;
			}
			else{
				pocet = 2;
			}

			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_AUG_25_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_MANZ); // 2006-08-07: upravené lebo žil v manželstve :)
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				mystrcpy(_global_svaty3.meno, text_AUG_25_CZ[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty3.farba = LIT_FARBA_CERVENA;
				_global_svaty3.kalendar = KALENDAR_VSEOBECNY_CZ;

				_global_svaty4.typslav = SLAV_SPOMIENKA;
				_global_svaty4.smer = 11; // miestne povinné spomienky
				_global_svaty4.typslav_lokal = LOKAL_SLAV_OSTRAVA_OPAVA;
				mystrcpy(_global_svaty4.meno, text_AUG_25_2_CZ[_global_jazyk], MENO_SVIATKU);
				_global_svaty4.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty4.farba = LIT_FARBA_CERVENA;
				_global_svaty4.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ, CZOP only

			if (_global_jazyk == JAZYK_HU){
				if (poradie_svaty == 3){

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY){
						set_spolocna_cast(sc, poradie_svaty);
					}
					// všetko je zo spoločnej časti na výročie posviacky chrámu

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;

					break;
				}

				pocet = 3;
				_global_svaty3.smer = 8; // miestne sviatky
				_global_svaty3.typslav = SLAV_SVIATOK;
				_global_svaty3.typslav_lokal = LOKAL_SLAV_KAL_KECS_FELSZ;
				mystrcpy(_global_svaty3.meno, text_AUG_25_HU[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = KALENDAR_VSEOBECNY_HU;
			}// HU only

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				mystrcpy(_global_svaty3.meno, text_AUG_25_OCD[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// KALENDAR_SK_OCD

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
				if (poradie_svaty == 5){

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					// _vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 5;
				_global_svaty5.smer = 12; // ľubovoľné spomienky
				_global_svaty5.typslav = SLAV_LUB_SPOMIENKA;
				mystrcpy(_global_svaty5.meno, text_AUG_25_SDB[_global_jazyk], MENO_SVIATKU);
				_global_svaty5.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
				_global_svaty5.farba = LIT_FARBA_BIELA;
				_global_svaty5.kalendar = _global_kalendar;
			}// KALENDAR_CZ_SDB

		}// všeobecný kalednár a špeciality

		break;

	case 26: // MES_AUG -- 26AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_AUG_26_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_antifon(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon(modlitba);

				break;
			}
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OCD_BOSE_KARMEL_SPOM;
			mystrcpy(_global_svaty1.meno, text_AUG_26_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// KALENDAR_SK_OCD

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_AUG_26_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 27: // MES_AUG -- 27AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){

				file_name_vlastny_kalendar(_global_kalendar);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

			}// kalendár pre KALENDAR_CZ_OPRAEM

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_MANZ); // 2006-08-19: upravené, lebo žila v manželstve
		_global_svaty1.farba = LIT_FARBA_BIELA;
		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			mystrcpy(_global_svaty1.meno, text_AUG_27_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM
		else{
			mystrcpy(_global_svaty1.meno, text_AUG_27[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 28: // MES_AUG -- 28AUG

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_AUG_28[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// pre modlitbu cez deň na slávnosť sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_AUG_28_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ) // v slovenskom breviári má vlastný hymnus, v českom nie | 2008-09-09; aj v dominikánskom má vlastný hymnus; 2009-09-09 | aj HU má vlastný hymnus; 2012-09-03
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ) // v slovenskom breviári má vlastný hymnus, v českom nie | 2008-09-09; aj v dominikánskom má vlastný hymnus; 2009-09-09 | aj HU má vlastný hymnus; 2012-09-03
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_AUG_28[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_AUG_28[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár a špeciality

		break;

	case 29: // MES_AUG -- 29AUG

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
			}
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_muc(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_AUG_29[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 30: // MES_AUG -- 30AUG

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_TRNAVA;
			_global_svaty1.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty1.meno, text_AUG_30_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_AUG_30_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 31: // MES_AUG -- 31AUG

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_ESZTERGOM_BUDA_FOEGYH;
			mystrcpy(_global_svaty1.meno, text_AUG_31_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;
	};

	return pocet;
}// sviatky_svatych_08_august()

short int sviatky_svatych_09_september(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_SEP;
	short int pom_poradie = 1;

	Log("mesiac september\n");
	switch (den){

	case 1: // MES_SEP -- 01SEP

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_HU_CONCEPTIONISTAK_UN;
			mystrcpy(_global_svaty1.meno, text_SEP_01_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_SEP_01_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 2: // MES_SEP -- 02SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_SEP_02_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_SEP_02_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_02_1_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_SEP_02_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_02_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 3: // MES_SEP -- 03SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_SEP_03[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 4: // MES_SEP -- 04SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_SEP_04_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_04_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		break;

	case 5: // MES_SEP -- 05SEP

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_05[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 6: // MES_SEP -- 06SEP

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KOSICE;
			mystrcpy(_global_svaty1.meno, text_SEP_06_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_SEP_06_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_SEP_06_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 7: // MES_SEP -- 07SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_ant_kcitresp_modl;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_SEP_07_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_HU)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_benediktus;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_magnifikat;
				}

				break;
			}
			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			}
			else if (_global_jazyk == JAZYK_SK){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
			}
			else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ, CZOP only
			mystrcpy(_global_svaty1.meno, text_SEP_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
		}// SK, CZ, CZOP, HU only

		break;

	case 8: // MES_SEP -- 08SEP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SVD)) || ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_SVD))) {
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

				set_popis_dummy();

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_SEP_08[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SVD, KALENDAR_HU_SVD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				// nemá popis
				if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
					set_popis_dummy();
				}

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				else{
					_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
				}

				_vlastna_cast_mcd_ant_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_SEP_08[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár
		break;

	case 9: // MES_SEP -- 09SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_09_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_09[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 10: // MES_SEP -- 10SEP

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_10_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_10_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 11: // MES_SEP -- 11SEP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OPRAEM_NOVA_RISE;
			mystrcpy(_global_svaty1.meno, text_OPATSKY_KOSTOL_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 12: // MES_SEP -- 12SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_SEP_12_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_benediktus;
				}

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_magnifikat;
				}

				break;
			}
			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			}// HU
			else{
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
			}// SK, CZ

			mystrcpy(_global_svaty1.meno, text_SEP_12[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
				if (poradie_svaty == 2){

					// úprava _anchor_head, nakoľko sa používajú rovnaké texty ako pre poradie_svaty == 1
					sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac]); // MES_SEP
					Log("  _anchor_head == %s\n", _anchor_head);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SPOMIENKA;
				_global_svaty2.smer = 11; // miestne povinné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE;
				mystrcpy(_global_svaty2.meno, text_SEP_12_OPRAEM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_CZ_OPRAEM
		}// všeobecný kalendár

		break;

	case 13: // MES_SEP -- 13SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_SEP_13[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 8; // miestne sviatky
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_GYORI_SZEKESEGYH_FELSZ;
			mystrcpy(_global_svaty2.meno, text_SEP_13_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 14: // MES_SEP -- 14SEP

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o sviatok Pana, ktora ma velku prioritu, a preto ma aj - ak je nedela - prve vespery 

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("14SEP | Povysenie sv. Kriza: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sv_kriz(modlitba);
			/*
			// 2014-09-14: doplnené prvé (ak padne na nedeľu)
			if(_global_den.denvt == DEN_NEDELA){
			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_nedela(modlitba);
			}
			*/
			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sv_kriz(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sv_kriz(modlitba);

			// žalmy pre mcd sú zo dňa, vyriešené pomocou ZALTAR_IBA_ZALMY_HYMNUS_MCD
			_vlastna_cast_mcd_ant_kcitresp_modl;

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sv_kriz(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 5; // sviatky Pána uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_SEP_14[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 15: // MES_SEP -- 15SEP

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		if (((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) && (_global_jazyk == JAZYK_SK)) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o slavnost (2006-09-12: len na Slovensku), ktora ma takmer najvacsiu prioritu, a preto ma aj prve vespery - a vtedy by to normalne nefungovalo; nastavenie veci pre modlitbu by sa muselo diat v predoslom dni, co je neciste riesenie

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("15SEP | Sedembolestnej Panny Marie, patronky Slovenska: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY){
				if (_global_jazyk == JAZYK_SK){
					set_spolocna_cast(sc, poradie_svaty);
				}
				else{
					// predpísané sú prosby zo spoločnej časti
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_PROSBY);
				}
			}

			// iba pre SK je to slávnosť
			if (_global_jazyk == JAZYK_SK){
				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_panien(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);
			}

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_full(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
				_vlastna_cast_full(modlitba);
			}// SK, HU only
			else{
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
			}

			if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}
			}// SK only

			modlitba = MODL_VESPERY;
			if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_full(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}
			_set_zalmy_sviatok_panien(modlitba);

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		if (_global_jazyk == JAZYK_SK){
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		}// SK only
		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP) || (_global_jazyk == JAZYK_HU)){
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		}
		mystrcpy(_global_svaty1.meno, text_SEP_15[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 16: // MES_SEP -- 16SEP

		pom_poradie = 1;

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				_set_zalmy_sviatok_muc(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_CECHY_SPOMIENKA;
			mystrcpy(_global_svaty1.meno, text_SEP_16_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

			pom_poradie = pocet = 2;
		}// CZ, CZOP only

		if (poradie_svaty == pom_poradie){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
			_global_svaty(pom_poradie).typslav = SLAV_SPOMIENKA;
			_global_svaty(pom_poradie).smer = 10; // povinné spomienky podľa všeobecného kalendára
		}
		else{
			_global_svaty(pom_poradie).typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty(pom_poradie).smer = 12; // ľubovoľné spomienky
			_global_svaty(pom_poradie).typslav_lokal = LOKAL_SLAV_LEN_MORAVA;
		}
		mystrcpy(_global_svaty(pom_poradie).meno, text_SEP_16[_global_jazyk], MENO_SVIATKU);
		// český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
		if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
		}
		else{
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_PAPEZ, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		}
		_global_svaty(pom_poradie).farba = LIT_FARBA_CERVENA;
		_global_svaty(pom_poradie).kalendar = KALENDAR_VSEOBECNY;

		break;

	case 17: // MES_SEP -- 17SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_SEP_17_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_17_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_duch_past(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_SEP_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky

			mystrcpy(_global_svaty1.meno, text_SEP_17[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;

				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_LEN_CECHY;
				mystrcpy(_global_svaty2.meno, text_SEP_16[_global_jazyk], MENO_SVIATKU);
				// český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
				if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
					_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
				}
				else{
					_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_PAPEZ, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
				}
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
			}// CZ only
		}// všeobecný kalendár

		break;

	case 18: // MES_SEP -- 18SEP

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					_vlastna_cast_modlitba_ina;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_SEP_18_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_SEP_18_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}// KALENDAR_CZ_OFMCAP

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_full_okrem_antifon(modlitba);
				}// KALENDAR_CZ_OFMCAP
				else{
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;
				}// KALENDAR_SK_OFM, KALENDAR_HU_OFM

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCONV;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty1.meno, text_SEP_18_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OPRAEM_DOKSANY;
			mystrcpy(_global_svaty1.meno, text_SEP_18_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 19: // MES_SEP -- 19SEP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_SEP_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_19[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
				mystrcpy(_global_svaty2.meno, text_SEP_19_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM
		}// všeobecný kalendár a špeciality

		break;

	case 20: // MES_SEP -- 20SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if ((_global_jazyk == JAZYK_CZ) && (poradie_svaty == 2)){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY){
				set_spolocna_cast(sc, poradie_svaty);
			}
			// všetko je zo spoločnej časti na výročie posviacky chrámu

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_SEP_20[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){

			pocet = 2;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_LITOMERICE;
			_global_svaty2.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty2.meno, text_SEP_20_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		break;

	case 21: // MES_SEP -- 21SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_1citanie;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_SEP_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 22: // MES_SEP -- 22SEP

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_NITRA;
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			mystrcpy(_global_svaty1.meno, text_SEP_22[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_SEP_22_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_SEP_22_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
			mystrcpy(_global_svaty2.meno, text_SEP_22_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_SEP_22_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty2.meno, text_SEP_22_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 23: // MES_SEP -- 23SEP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				if (_global_jazyk != JAZYK_HU){
					file_name_vlastny_kalendar(_global_kalendar);
				}// HU: ordinary texts

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_SEP_23_OFM[_global_jazyk], MENO_SVIATKU); // ToDo: HU has: "Assisi Szent Klára testének átvitele"
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_SEP_23[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 24: // MES_SEP -- 24SEP

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_BYSTRICA;
			mystrcpy(_global_svaty1.meno, text_SEP_24_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		else if (_global_jazyk == JAZYK_HU){
			// SZENT GELLÉRT PÜSPÖK ÉS VÉRTANÚ | Ünnep
			// A SZEGED-CSANÁDI EGYHÁZMEGYÉBEN: SZENT GELLÉRT PÜSPÖK ÉS VÉRTANÚ, A SZEGED-CSANÁDI EGYHÁZMEGYE VÉDŐSZENTJE

			// nie je slávnosť vo všeobecnom maďarskom kalendári, ale len sviatok
			if (poradie_svaty == 1){
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_muc(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_muc(modlitba);
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZEGED_CSAN_PATRON2;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_SEP_24_HU[_global_jazyk], MENO_SVIATKU);
		}// HU only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_SEP_24_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 25: // MES_SEP -- 25SEP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_SEP_25_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_prosby;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_prosby;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_SEP_25_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 26: // MES_SEP -- 26SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_SEP_26[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		// všeobecný kalendár

		if (_global_jazyk == JAZYK_CZ_OP){

			pocet = 2;

			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_SEP_28_OP[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_SEP_26_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_SEP_26_OFM[_global_jazyk], MENO_SVIATKU); // HU: different saints!
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_SEP_26_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR

		break;

	case 27: // MES_SEP -- 27SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_SEP_27[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 28: // MES_SEP -- 28SEP

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){ // odvetvené len pre Česko; prevzaté podľa cyrila a metoda
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_opt[OPT_3_SPOLOCNA_CAST] = MODL_SPOL_CAST_MUCENIK;
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_SEP_28[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
				// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o slavnost, ktora ma takmer najvacsiu prioritu, a preto ma aj prve vespery - a vtedy by to normalne nefungovalo; nastavenie veci pre modlitbu by sa muselo diat v predoslom dni, co je neciste riesenie

				// definovanie parametrov pre modlitbu
				sc = _decode_spol_cast(_global_svaty1.spolcast);
				Log("28SEP | CZ: Svatý Václav: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_ANTIFONY);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full_okrem_antifon(modlitba);
				_set_zalmy_sviatok_muc(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;
				// _set_zalmy_sviatok_muc(modlitba); | netreba, zabezpečí predsunutie priradení navrch a volanie set_spolocna_cast()

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_muc(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
					break;
				}
			}
		}// CZ only

		else{
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				if (poradie_svaty == 1){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_prosieb(modlitba);
					_vlastna_cast_modlitba_ina;

					break;
				}
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 11; // miestne povinné spomienky
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				mystrcpy(_global_svaty1.meno, text_SEP_28_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}// kalendár pre KALENDAR_SK_OP

			else{
				// pre dominikánov czop sa slávi 26.9.
				if (poradie_svaty == 1){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}
				mystrcpy(_global_svaty1.meno, text_SEP_28[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
				_global_svaty1.farba = LIT_FARBA_CERVENA;
				_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
				// na Slovensku sv. Václav len ľubovoľná spomienka
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky

				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_SEP_28_2[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
				_global_svaty2.farba = LIT_FARBA_CERVENA;
				_global_svaty2.kalendar = KALENDAR_VSEOBECNY;
			}// všeobecný kalendár

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_SEP_28_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM
		}// excluding CZ

		break;

	case 29: // MES_SEP -- 29SEP
		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_archanjelov(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_archanjelov(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_archanjelov(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_SEP_29[_global_jazyk], MENO_SVIATKU);
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_VACI_PATRON;
		}
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 30: // MES_SEP -- 30SEP

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			if (_global_jazyk != JAZYK_CZ){ // 2008-10-12: odvetvené len pre Slovensko; 2010-10-06: pridané aj pre CZOP
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_SEP_30[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;
	};

	return pocet;
}// sviatky_svatych_09_september()

short int sviatky_svatych_10_oktober(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_OCT;
	short int pom_poradie = 1;

	Log("mesiac október\n");
	switch (den){

	case 1: // MES_OCT -- 01OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_ocd_terezka(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_ocd_terezka(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_set_zalmy_ocd_terezka(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_OKT_01_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_01[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 2: // MES_OCT -- 02OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			set_popis_dummy();

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_anjelov_strazcov(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_kcitresp_modl;

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_anjelov_strazcov(modlitba);

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_OKT_02[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 3: // MES_OCT -- 03OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_03_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_OKT_03_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 4: // MES_OCT -- 04OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ofm_frantisek(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ofm_frantisek(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ofm_frantisek(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_ofm_frantisek(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_04_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_set_zalmy_pc_1_8_16(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_vlastna_cast_modlitba_ina; // Alebo ako na ranné chvály.

				_vlastna_cast_mcd_ant_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_OKT_04_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_04[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){

				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full_okrem_antifon(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_OKT_04_OP[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 5: // MES_OCT -- 05OKT

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_CZ_OP;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_OKT_05_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_OKT_05_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_05_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_05_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR

		if ((_global_jazyk == JAZYK_SK) && ((_global_kalendar == KALENDAR_VSEOBECNY_SK) || (_global_kalendar == KALENDAR_VSEOBECNY) || (_global_kalendar == KALENDAR_NEURCENY))){
			if (poradie_svaty == 1){

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KONGREGACIA_SMBM;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_05_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_VESZPREM_FOEGYH;
			mystrcpy(_global_svaty1.meno, text_OKT_05_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 6: // MES_OCT -- 06OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_OKT_06[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_06_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_06_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_06_HU_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 7: // MES_OCT -- 07OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				_vlastna_cast_modlitba_ina; // Alebo ako na ranné chvály.

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_vlastna_cast_modlitba_ina; // Alebo ako na ranné chvály.

				_vlastna_cast_mcd_ant_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_OKT_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					if (_global_jazyk != JAZYK_CZ){
						set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_PROSBY); // prosby zo spoločnej časti
					}
					else{
						// predpísané sú prosby zo spoločnej časti
						set_spolocna_cast(sc, poradie_svaty);
					}
				}

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // 2008-10-15: odvetvené len pre Slovensko; 2009-07-09: pridané aj pre CZ_OP
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
				}
				_set_zalmy_1nedele_rch(); // 2011-10-07: doplnené podľa LH

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ_OP)){ // 2008-10-15: odvetvené len pre Slovensko; 2009-07-09: pridané aj pre CZ_OP
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
				}
				_set_zalmy_sviatok_marie(modlitba); // 2011-10-07: doplnené podľa LH

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){

				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full_okrem_antifon(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_PRVE_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					modlitba = MODL_KOMPLETORIUM;
					_set_kompletorium_slavnost(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SLAVNOST;
				_global_svaty2.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_OKT_07[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY){
						set_spolocna_cast(sc, poradie_svaty);
					}
					// všetko je zo spoločnej časti na výročie posviacky chrámu

					break;
				}

				pocet = 2;
				_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
				_global_svaty2.typslav = SLAV_SLAVNOST;
				_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_ZELIV;
				mystrcpy(_global_svaty2.meno, text_OPATSKY_KOSTOL_OPRAEM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_CZ_OPRAEM
		}// všeobecný kalendár

		break;

	case 8: // MES_OCT -- 08OKT

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){

			// presúva sa 07OKT na 8. října pre KALENDAR_CZ_OPRAEM (LOKAL_SLAV_OPRAEM_ZELIV)
			sprintf(_anchor_head, "%02d%s_", 7, nazov_MES[mesiac]); // MES_OKT
			Log("  _anchor_head == %s\n", _anchor_head);

			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_OPRAEM_ZELIV;
			mystrcpy(_global_svaty1.meno, text_OKT_07[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_OKT_08_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_08_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			if (((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)) && (_global_jazyk == JAZYK_HU)){
				// definovanie parametrov pre modlitbu
				sc = _decode_spol_cast(_global_svaty1.spolcast);
				Log("08OKT | HU: Szűz Mária, Magyarok Nagyasszonya, Magyarország főpátronája: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_panien(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}
				else{
					_vlastna_cast_full(modlitba);
				}
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_sviatok_panien(modlitba);

				if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
					break;
				}
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_OKT_08_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 9: // MES_OCT -- 09OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_09_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_09_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_09_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

			if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 3){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_SPOMIENKA;
				_global_svaty3.smer = 11; // miestne povinné spomienky
				mystrcpy(_global_svaty3.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty3.meno, text_OKT_09_OP[_global_jazyk]);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty3.farba = LIT_FARBA_BIELA;
				_global_svaty3.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 10: // MES_OCT -- 10OKT

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_10_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_10_HU_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 11: // MES_OCT -- 11OKT

		if (_global_jazyk == JAZYK_SK){
			pom_poradie = 2;
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_ZILINA;
			mystrcpy(_global_svaty1.meno, text_OKT_11_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			pom_poradie = 3;
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_11_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){

			pom_poradie = 3;

			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_11_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_HU) || (_global_jazyk == JAZYK_CZ)){
			pom_poradie = 1; // poradie spomienky Jána XXIII.
		}

		if (poradie_svaty == pom_poradie){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			// keďže poradie v rámci SK LH sa môže meniť (propriá OP/OFM), používame napevno "11OKT_" | pre POPIS je potrebné použiť "11OKT2_" aj "11OKT3_"
			sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac]); // MES_OKT
			Log("  _anchor_head == %s\n", _anchor_head);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}

		pocet = pom_poradie;
		_global_svaty(pom_poradie).typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty(pom_poradie).smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty(pom_poradie).meno, text_OKT_11[_global_jazyk], MENO_SVIATKU);
		_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty(pom_poradie).farba = LIT_FARBA_BIELA;
		_global_svaty(pom_poradie).kalendar = KALENDAR_VSEOBECNY;

		break;

	case 12: // MES_OCT -- 12OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCAP;
			}
			else if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_OKT_12_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_12_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ only

		break;

	case 13: // MES_OCT -- 13OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_13_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_OKT_13_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_13_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_OKT_13_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 14: // MES_OCT -- 14OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_14_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_14_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 15: // MES_OCT -- 15OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_ocd_terezia(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_ocd_terezia(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_ocd_terezia(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_set_zalmy_ocd_terezia(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_15_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk != JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_15[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 16: // MES_OCT -- 16OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_CSSR)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_CSSR))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_OKT_16_CSSR[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_CSSR a KALENDAR_CZ_CSSR

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				if (je_CZ_hymny_k_volnemu_vyberu){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_16_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_16_2[_global_jazyk], MENO_SVIATKU);
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_global_svaty2.typslav_lokal = LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST;
			}
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL, MODL_SPOL_CAST_SV_ZENA_REHOLNIK, MODL_SPOL_CAST_SV_ZENA_MANZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 17: // MES_OCT -- 17OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_OKT_17[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 18: // MES_OCT -- 18OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty, (je_CZ_hymny_k_volnemu_vyberu) ? FORCE_BRAT_HYMNUS : FORCE_NEBRAT);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_full_okrem_hymnu(modlitba);
			}
			else{
				_vlastna_cast_full(modlitba);
			}

			modlitba = MODL_POSV_CITANIE;
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_full_okrem_hymnu_antifon_a_prosieb(modlitba);
			}
			else{
				_vlastna_cast_full_okrem_antifon_a_prosieb(modlitba);
			}

			_vlastna_cast_mcd_kcitresp_modl;

			modlitba = MODL_VESPERY;
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_full_okrem_hymnu(modlitba);
			}
			else{
				_vlastna_cast_full(modlitba);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_OKT_18[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 19: // MES_OCT -- 19OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_19_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_19_1[_global_jazyk], MENO_SVIATKU);
			// český breviár nemá možnosť pre duch. pastierov "pre viacerých" -- MODL_SPOL_CAST_DUCH_PAST_VIACERI
			if ((_global_jazyk != JAZYK_CZ) && (_global_jazyk != JAZYK_CZ_OP)){
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			}
			else{
				_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			}
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_19_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			_global_svaty3.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty3.meno, text_OKT_19_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk == JAZYK_HU) {
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk != JAZYK_SK){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}// KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk != JAZYK_SK) {
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}// KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}// KALENDAR_HU_OFM
			else{
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty3.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty3.meno, text_OKT_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty3.farba = LIT_FARBA_BIELA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		break;

	case 20: // MES_OCT -- 20OKT

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_OKT_20_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_2citanie;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_HU){
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_20_OFM[_global_jazyk], MENO_SVIATKU); // HU: different saint!
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		break;

	case 21: // MES_OCT -- 21OKT

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_21_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			// 2013-12-11, e-mail od Mareka OPraem: památka sv. Voršily (21. října): texty ze Společných textů o více mučednících vyjma 2. čtení v Modlitbě se čtením. Toto 2. čtení v modlitbě se čtením se má vybrat z několika nabízených dle propria – navrhl bych, aby se vybralo jedno, a nastálo se pak uvádělo v mobilní verzi; zde bych navrhl 2. čtení pro památku sv. Stanislava, biskupa a mučedníka (11. dubna). Ti pak, kdo užívají běžné tištěné texty, ať si vyberou dle nabídky v knize propria…
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				// _vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				// _vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				// _vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 11; // miestne povinné spomienky
			_global_svaty2.typslav_lokal = LOKAL_SLAV_OPRAEM_STRAHOV;
			mystrcpy(_global_svaty2.meno, text_OKT_21_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_SV_ZENA_VIACERE);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_OKT_21_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 22: // MES_OCT -- 22OKT

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;
					_vlastna_cast_2citanie;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

				}

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_CZ_OP;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_OKT_22_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_OKT_22_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		// ToDo: doriešiť pre SK OP

		if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_CZ)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_22[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
		}// CZ, SK only

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			else if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KONSEKR_KOSTOLY_HU;
			mystrcpy(_global_svaty1.meno, text_OKT_26[_global_jazyk], MENO_SVIATKU); // SK: 26OKT; HU: 22OKT
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_22[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;

			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				if (poradie_svaty == 3){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_magnifikat;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 3;
				_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty3.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty3.meno, text_OKT_22_HU_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_MUCENICA);
				_global_svaty3.farba = LIT_FARBA_CERVENA;
				_global_svaty3.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_HU_OFM

		}// HU only

		break;

	case 23: // MES_OCT -- 23OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk != JAZYK_SK){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}// KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
					_vlastna_cast_prosby;
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_kcitanie;
					_vlastna_cast_kresponz;
					_vlastna_cast_prosby;
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_OKT_23_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			if (_global_jazyk == JAZYK_HU){
				// 2013-10-24: HU: obligatory
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
				_global_svaty1.typslav_lokal = LOKAL_SLAV_KATONAI_ORDINARIAT;
			}
			else{
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
			}
			mystrcpy(_global_svaty1.meno, text_OKT_23[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 24: // MES_OCT -- 24OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_OKT_24[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_24_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty2.typslav = SLAV_SLAVNOST;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_SZEGED_CSAN_EGYH2;
			mystrcpy(_global_svaty2.meno, text_OKT_24_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 25: // MES_OCT -- 25OKT

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SPIS;
			mystrcpy(_global_svaty1.meno, text_OKT_25_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KONSEKR_KOSTOLY_CZ;
			mystrcpy(_global_svaty1.meno, text_OKT_26[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ only

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_25_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_PECS_PATRON;
		}// HU only

		// výnimočne sú zlúčené propriá pre SK SDB a CZ OFMCap
		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))){

			file_name_vlastny_kalendar(_global_kalendar);

			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty2.typslav = SLAV_SLAVNOST;
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)){
				_global_svaty2.typslav_lokal = LOKAL_SLAV_KONSEKR_KOSTOLY;
			}// KALENDAR_SK_SDB
			mystrcpy(_global_svaty2.meno, text_OKT_25_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB resp. KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_25_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_25_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_PANNY_VIACERE, MODL_SPOL_CAST_SV_ZENA_VIACERE);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		break;

	case 26: // MES_OCT -- 26OKT

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KONSEKR_KOSTOLY;
			mystrcpy(_global_svaty1.meno, text_OKT_26[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_26_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_OKT_26_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_OKT_26_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 27: // MES_OCT -- 27OKT

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_ROZNAVA;
			mystrcpy(_global_svaty1.meno, text_OKT_27_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_26_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 28: // MES_OCT -- 28OKT

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (!je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_OKT_28[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 29: // MES_OCT -- 29OKT

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_29_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_29_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.typslav_lokal = LOKAL_SLAV_BRNO;
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		break;

	case 30: // MES_OCT -- 30OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_30_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_OKT_30_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_OKT_30_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_HRADEC_KRALOVE;
			_global_svaty1.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty1.meno, text_OKT_30_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				set_popis_dummy();

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_OKT_30_HU_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		break;

	case 31: // MES_OCT -- 31OKT

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_31_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_31_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_31_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_benediktus;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_OKT_31_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_CZ_OFMCAP
		}// CZ, CZOP only

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_OKT_31_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;
	};

	return pocet;
}// sviatky_svatych_10_oktober()

short int sviatky_svatych_11_november(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_NOV;
	short int pom_poradie = 1;

	Log("mesiac november\n");
	switch (den){

	case 1: // MES_NOV -- 01NOV

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o sviatok Pana, ktora ma velku prioritu, a preto ma aj - ak je nedela - prve vespery 

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("01NOV | Všetkých svätých: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY){
				set_spolocna_cast(sc, poradie_svaty);
			}

			set_popis_dummy();

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_vsetkych_svatych(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_vsetkych_svatych(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_vsetkych_svatych(modlitba);

			_vlastna_cast_mcd_ant_kcitresp_modl;

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_vsetkych_svatych(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			// pre dominikánov môžu byť niektoré časti vlastné
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){

				file_name_vlastny_kalendar(_global_kalendar);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_kresponz;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
			}// kalendár pre KALENDAR_SK_OP

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		_global_svaty1.prik = PRIKAZANY_SVIATOK;
		mystrcpy(_global_svaty1.meno, text_NOV_01[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 2: // MES_NOV -- 02NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			/*
			// pre SK je tam rubrika... radšej to tu nechám len pre istotu do budúcnosti
			if((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
			set_popis_dummy();
			}
			*/

			modlitba = MODL_RANNE_CHVALY;
			if ((_global_jazyk == JAZYK_CZ) && (!je_CZ_hymny_k_volnemu_vyberu)){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			if (_global_jazyk != JAZYK_CZ_OP){
				_vlastna_cast_modlitba;
			}

			modlitba = MODL_POSV_CITANIE;
			// ak padne toto slávenie na nedeľu, berie sa nedeľné ofícium
			if (_global_den.denvt != DEN_NEDELA){
				_vlastna_cast_2citanie;
				if (_global_jazyk != JAZYK_CZ_OP){
					_vlastna_cast_modlitba;
				}
			}

			// vlastná modlitba pre modlitbu cez deň (ostatné opravené: berie sa z ofícia za zosnulých)
			if (_global_jazyk != JAZYK_CZ_OP){
				_vlastna_cast_mcd_modlitba;
			}

			modlitba = MODL_VESPERY;
			if ((_global_jazyk == JAZYK_CZ) && (!je_CZ_hymny_k_volnemu_vyberu)){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			if (_global_jazyk != JAZYK_CZ_OP){
				_vlastna_cast_modlitba;
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		// ak padne toto slávenie na nedeľu, berie sa nedeľné ofícium
		if (_global_den.denvt != DEN_NEDELA){
			_global_svaty1.smer = 3; // všetkých verných zosnulých (podľa Tabuľky liturgických dní usporiadaných podľa prednosti)
		}
		else{
			_global_svaty1.smer = 10; // všetkých verných zosnulých; bolo 12 (len "ľubovoľné" slávenie), zmenil som na spomienku (10)
		}
		mystrcpy(_global_svaty1.meno, text_NOV_02[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
		_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 3: // MES_NOV -- 03NOV

	label_03NOV :

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			// alebo keď je v tento deň prekážka, tak najbližší voľný deň (vyriešené cez label_03NOV)
			if (poradie_svaty == 1){

				sprintf(_anchor_head, "%02d%s_", 2, nazov_MES[mesiac]); // MES_NOV // 2. čítanie: 02NOV (použité natvrdo kvôli prípadnému prekladaniu na 05NOV)
				Log("  _anchor_head == %s\n", _anchor_head);
				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac]); // MES_NOV // späť: 03NOV (použité natvrdo kvôli prípadnému prekladaniu na 05NOV)
				Log("  _anchor_head == %s\n", _anchor_head);

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

				set_popis_dummy();

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			mystrcpy(_global_svaty1.meno, text_NOV_03_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;
				}// kalendár pre KALENDAR_SK_OP

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_03[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
				_global_svaty1.typslav = SLAV_SVIATOK;
				_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				_global_svaty1.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OP

			else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_2citanie;
					_vlastna_cast_modlitba;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12; // ľubovoľné spomienky
				mystrcpy(_global_svaty2.meno, text_NOV_03_SJ[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_SJ

			else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				// ToDo: alebo keď je v tento deň prekážka, tak najbližší voľný deň (neriešené pre SK, pretože spomienka je to len pre 2 z 3 rádov)
				if (poradie_svaty == 2){

					file_name_vlastny_kalendar(_global_kalendar);

					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_modlitba;

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_modlitba;

					_vlastna_cast_mcd_modlitba;

					modlitba = MODL_VESPERY;
					_vlastna_cast_modlitba;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty2.smer = 12;
				_global_svaty2.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP;
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
				_global_svaty2.farba = LIT_FARBA_FIALOVA_CIERNA;
				mystrcpy(_global_svaty2.meno, text_NOV_03_OFM[_global_jazyk], MENO_SVIATKU);
				_global_svaty2.kalendar = _global_kalendar;
			}// kalendár pre KALENDAR_SK_OFM

			else if (_global_jazyk == JAZYK_CZ_OP){
				if (poradie_svaty == 2){
					// definovanie parametrov pre modlitbu
					if (query_type != PRM_DETAILY)
						set_spolocna_cast(sc, poradie_svaty);

					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;

					modlitba = MODL_RANNE_CHVALY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					modlitba = MODL_POSV_CITANIE;
					_vlastna_cast_full(modlitba);

					modlitba = MODL_VESPERY;
					_vlastna_cast_full_okrem_prosieb(modlitba);

					_vlastna_cast_mcd_kcitresp_modl;

					break;
				}

				pocet = 2;
				_global_svaty2.typslav = SLAV_SVIATOK;
				_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
				mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty2.meno, text_NOV_03[_global_jazyk]);
				_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
				_global_svaty2.farba = LIT_FARBA_BIELA;
				_global_svaty2.kalendar = KALENDAR_CZ_OP;
			}// CZOP only
		}// všeobecný kalendár

		break;

	case 4: // MES_NOV -- 04NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_04[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 5: // MES_NOV -- 05NOV

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP) && (_global_den.denvt == DEN_UTOROK)){
			// t.j. Vzpomínka na všechny zemřelé serafínského řádu padla na nedeľu; pondelok 04NOV je památka Karla Boromejského, a to byl kardinál-protektor řádu
			sprintf(_anchor_head, "%02d%s_", den - 2, nazov_MES[mesiac]); // MES_NOV
			Log("  _anchor_head == %s\n", _anchor_head);
			Log("jumping to label_03NOV...\n");
			goto label_03NOV;
		}
		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_NOV_05_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_TT_BB_KE_NR_RO;
			mystrcpy(_global_svaty1.meno, text_NOV_05_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_antifon(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_NOV_05_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_05_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty2.meno, text_NOV_05_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty2.farba = LIT_FARBA_FIALOVA_CIERNA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_NOV_05_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP
		break;

	case 6: // MES_NOV -- 06NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_06_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_06_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					modlitba = MODL_INVITATORIUM;
					_vlastna_cast_antifona_inv;
				}

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					_vlastna_cast_antifony;
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_NOV_06_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_NOV_06_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 7: // MES_NOV -- 07NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_07_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				if (_global_jazyk == JAZYK_CZ_OP){
					// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					_set_zalmy_pc_1_8_16(modlitba);
				}// CZOP
				else{
					// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					_set_zalmy_pc_15_66(modlitba);
				}// KALENDAR_SK_OP

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
				if (_global_jazyk == JAZYK_CZ_OP){
					// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					_set_zalmy_vesp_110_116_ef(modlitba);
				}
				else{// KALENDAR_SK_OP
					// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
					_set_zalmy_vesp_89_98_kol(modlitba);
				}

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 11; // sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari - zmenené na ľubovoľné
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_NOV_07_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_NOV_07_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		break;

	case 8: // MES_NOV -- 08NOV

		if ((_global_jazyk == JAZYK_CZ_OP) || ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP))){
			if (poradie_svaty == 1){

				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					file_name_vlastny_kalendar(_global_kalendar);
				}

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_prosby;
				}
				else{
					_vlastna_cast_benediktus;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
					_vlastna_cast_1citanie;
					_vlastna_cast_2citanie;
				}
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if (_global_jazyk == JAZYK_CZ_OP){
					_vlastna_cast_prosby;
				}
				else{
					_vlastna_cast_magnifikat;
				}
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12;
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			if (_global_jazyk == JAZYK_CZ_OP){
				mystrcpy(_global_svaty1.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
				strcat(_global_svaty1.meno, text_NOV_08_OP[_global_jazyk]);
				_global_svaty1.kalendar = KALENDAR_CZ_OP;
			}
			else
			{
				mystrcpy(_global_svaty1.meno, text_NOV_08_OP[_global_jazyk], MENO_SVIATKU);
				_global_svaty1.kalendar = KALENDAR_SK_OP;
			}
		}// CZOP only, kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_08_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_benediktus;
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_magnifikat;
				}// KALENDAR_CZ_OFMCAP
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty1.meno, text_NOV_08_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba); // PROSBY ze Společných textů svatých mužů
				_set_zalmy_1nedele_rch();

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;
				_set_zalmy_sviatok_muc(modlitba, 2); // Žalmy a kantykum ze Společných textů více mučedníků

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba); // PROSBY ze Společných textů svatých mužů
				_set_zalmy_sviatok_muc(modlitba, 2); // Žalmy a kantykum ze Společných textů více mučedníků

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			mystrcpy(_global_svaty1.meno, text_NOV_08_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 9: // MES_NOV -- 09NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY){
				set_spolocna_cast(sc, poradie_svaty);
			}
			// všetko je zo spoločnej časti na výročie posviacky chrámu

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_2citanie;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 5; // sviatky Pána uvedené vo všeobecnom kalendári | povodne: 7; sviatky preblahoslavenej Panny Marie a svatych, uvedene vo vseobecnom kalendari; lenze 9. NOV 1997 mal tento sviatok prednost pred 32. nedelou v ocr, takze smer == 5
		mystrcpy(_global_svaty1.meno, text_NOV_09[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 10: // MES_NOV -- 10NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_10[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 11: // MES_NOV -- 11NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_set_zalmy_1nedele_rch();
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}// SK, HU
			else{
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;
			if (_global_jazyk == JAZYK_SK){
				_vlastna_cast_hymnus_ako_na_vespery(modlitba, _global_den.litobd); // hymnus ako na vešpery -- musí byť posledný pre danú modlitbu
			}

			modlitba = MODL_VESPERY;
			_set_zalmy_sviatok_duch_past(modlitba);
			if ((_global_jazyk == JAZYK_SK) || (_global_jazyk == JAZYK_HU)){
				_vlastna_cast_full_okrem_prosieb(modlitba);
			}// SK, HU
			else{
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_11[_global_jazyk], MENO_SVIATKU);
		if (_global_jazyk == JAZYK_SK){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SPIS_BA_PATRON;
		}
		else if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZOMBATHELYI_PATRON;
		}
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 12: // MES_NOV -- 12NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_12[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 13: // MES_NOV -- 13NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_13_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_ZALMY);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_full_okrem_ant;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_NOV_13_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_13_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_1nedele_rch();
				// pre dominikánov prosby zo spol. časti, pre český breviár: z vlastnej časti
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_full(modlitba);
				}
				else{
					// _global_jazyk == JAZYK_CZ_OP
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_1citanie;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				// pre dominikánov prosby zo spol. časti, pre český breviár: z vlastnej časti
				if (_global_jazyk == JAZYK_CZ){
					_vlastna_cast_full(modlitba);
				}
				else{
					// _global_jazyk == JAZYK_CZ_OP
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}

				// modlitba cez deň, totiž kedysi bol "sviatok", teraz "spomienka"; upozornil Mgr. Martin Kubeš, notář | _vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_NOV_13_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);
				// všetko je zo spoločnej časti pre sviatky svätých mužov

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_13_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				pom_poradie = 2;
			}
			else{
				pom_poradie = 1;
			}
			if (poradie_svaty == pom_poradie){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = pom_poradie; // HU
			_global_svaty(pom_poradie).typslav = SLAV_LUB_SPOMIENKA;
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty(pom_poradie).typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			}
			_global_svaty(pom_poradie).smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty(pom_poradie).meno, text_NOV_13_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(pom_poradie).spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty(pom_poradie).farba = LIT_FARBA_BIELA;
			_global_svaty(pom_poradie).kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		break;

	case 14: // MES_NOV -- 14NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_ocd_vsetci_svati(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_ocd_vsetci_svati(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_set_zalmy_ocd_vsetci_svati(modlitba);
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári | hoci technicky by malo byť: 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_NOV_14_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			if (_global_jazyk == JAZYK_HU){
				_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty1.smer = 12; // ľubovoľné spomienky
			}// HU
			else{
				_global_svaty1.typslav = SLAV_SPOMIENKA;
				_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			mystrcpy(_global_svaty1.meno, text_NOV_14_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_VIACERI, MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_14_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){
				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_NOV_14_1_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty2.meno, text_NOV_14_2_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_14_OPRAEM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OPRAEM

		break;

	case 15: // MES_NOV -- 15NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			// alebo keď je v tento deň prekážka, tak najbližší voľný deň
			if (poradie_svaty == 1){

				sprintf(_anchor_head, "%02d%s_", 2, nazov_MES[mesiac]); // MES_NOV // 2. čítanie: 02NOV (použité natvrdo kvôli prípadnému prekladaniu)
				Log("  _anchor_head == %s\n", _anchor_head);
				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac]); // MES_NOV // späť (použité natvrdo kvôli prípadnému prekladaniu)
				Log("  _anchor_head == %s\n", _anchor_head);

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				// ToDo: vigília

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			mystrcpy(_global_svaty1.meno, text_NOV_15_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_NOV_15[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_15[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if (_global_jazyk == JAZYK_CZ_OP){

			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_NOV_15[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			_global_svaty2.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SPOMIENKA_FMA : LOKAL_SLAV_SPOMIENKA_FMA_CZ;
			mystrcpy(_global_svaty2.meno, text_NOV_15_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 16: // MES_NOV -- 16NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_16_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_19_OFM[_global_jazyk], MENO_SVIATKU); // HU: 16NOV; SK OFM: 19NOV
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_16_1[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_MANZ, MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár; 1. svätec aj pre HU

		if (_global_jazyk != JAZYK_HU){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_NOV_16_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár (okrem HU)

		break;

	case 17: // MES_NOV -- 17NOV

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_16_2[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		else if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_sviatok_panien(modlitba);
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_vlastna_cast_full_okrem_kcit(modlitba);
				}// KALENDAR_SK_OFM
				else{
					_vlastna_cast_full(modlitba);
				}

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_panien(modlitba);
				if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
					_vlastna_cast_full_okrem_prosieb(modlitba);
				}// KALENDAR_SK_OFM
				else{
					_vlastna_cast_full(modlitba);
				}

				if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
					_vlastna_cast_mcd_full_okrem_ant;
				}// KALENDAR_CZ_OFMCAP
				else{
					_vlastna_cast_mcd_kcitresp_modl;
				}

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_NOV_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				if (_global_jazyk == JAZYK_CZ){
					// 2009-11-17: odvetvené pre český breviář
					_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				}
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_NOV_17[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL); // v breviári je len: "pre tých, čo konali skutky milosrdenstva"
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 18: // MES_NOV -- 18NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_NOV_18[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_NOV_18_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_HU_OFM

		break;

	case 19: // MES_NOV -- 19NOV

		if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				// psalmódia: Zsoltárok a Szent asszonyok közös zsolozsmájából.
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_NOV_17_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);
				// žalmy, ktoré zatiaľ nikde inde nie sú v tomto radení použité
				_set_zalmy_pc_45_87(modlitba);
				// _vlastna_cast_1citanie; // je síce zo spol. časti (skm), ale iné krátke resp. po čítaní

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_NOV_17[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL); // v SK breviári je len: "pre tých, čo konali skutky milosrdenstva"
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SPOMIENKA_OSC;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_19_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_19_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_NOV_19_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		break;

	case 20: // MES_NOV -- 20NOV

		if (_global_jazyk == JAZYK_SK){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 8; // miestne sviatky
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_NITRA;
			mystrcpy(_global_svaty1.meno, text_NOV_20_SK[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_SK;
		}// SK only

		break;

	case 21: // MES_NOV -- 21NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 22: // MES_NOV -- 22NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_NOV_22[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 23: // MES_NOV -- 23NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		else if (poradie_svaty == 2){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_NOV_23_1[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		pocet = 2;
		_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty2.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty2.meno, text_NOV_23_2[_global_jazyk], MENO_SVIATKU);
		_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
		_global_svaty2.farba = LIT_FARBA_BIELA;
		_global_svaty2.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 3){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 3;
			_global_svaty3.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty3.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty3.meno, text_NOV_23_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty3.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
			_global_svaty3.farba = LIT_FARBA_CERVENA;
			_global_svaty3.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 24: // MES_NOV -- 24NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_NOV_24_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		else if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
			// ToDo: alebo keď je v tento deň prekážka, tak najbližší voľný deň
			if (poradie_svaty == 1){

				sprintf(_anchor_head, "%02d%s_", 2, nazov_MES[mesiac]); // MES_NOV // 2. čítanie: 02NOV (použité natvrdo kvôli prípadnému prekladaniu)
				Log("  _anchor_head == %s\n", _anchor_head);
				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac]); // MES_NOV // späť: 24NOV (použité natvrdo kvôli prípadnému prekladaniu)
				Log("  _anchor_head == %s\n", _anchor_head);

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty, FORCE_BRAT_VSETKO);

				set_popis_dummy();

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty1.farba = LIT_FARBA_FIALOVA_CIERNA;
			mystrcpy(_global_svaty1.meno, text_NOV_03_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_HU_OFM

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_NOV_24[(_global_jazyk == JAZYK_CZ_OP) ? JAZYK_CZ : _global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		if (_global_jazyk == JAZYK_CZ_OP){

			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				_vlastna_cast_mcd_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_full_okrem_prosieb_a_hymnu(modlitba);

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SVIATOK;
			_global_svaty2.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty2.meno, text_PRO_OP[_global_jazyk], MENO_SVIATKU);
			strcat(_global_svaty2.meno, text_NOV_24_OP[_global_jazyk]);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty2.farba = LIT_FARBA_CERVENA;
			_global_svaty2.kalendar = KALENDAR_CZ_OP;
		}// CZOP only

		break;

	case 25: // MES_NOV -- 25NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_NOV_25[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_MUCENICA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_SPOMIENKA;
			_global_svaty2.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty2.meno, text_NOV_25_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_ZA_ZOSNULYCH);
			_global_svaty2.farba = LIT_FARBA_FIALOVA_CIERNA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 2){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				break;
			}

			pocet = 2;
			_global_svaty2.smer = 4; // miestne slávnosti podľa miestneho kalendára
			_global_svaty2.typslav = SLAV_SLAVNOST;
			_global_svaty2.typslav_lokal = LOKAL_SLAV_SZEKESFEHERVAR_EGYH;
			mystrcpy(_global_svaty2.meno, text_NOV_25_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 26: // MES_NOV -- 26NOV

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_26_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_26_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		break;

	case 27: // MES_NOV -- 27NOV

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_NOV_27_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_27_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP

		break;

	case 28: // MES_NOV -- 28NOV

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){

			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			if ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM)){
				_global_svaty(1).typslav = SLAV_SPOMIENKA;
				_global_svaty(1).smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			}
			else{
				_global_svaty(1).typslav = SLAV_LUB_SPOMIENKA;
				_global_svaty(1).smer = 12; // ľubovoľné spomienky
			}
			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				_global_svaty(1).typslav_lokal = LOKAL_SLAV_SPOMIENKA_OFM;
			}// KALENDAR_SK_OFM
			mystrcpy(_global_svaty(1).meno, text_NOV_28_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty(1).spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty(1).farba = LIT_FARBA_BIELA;
			_global_svaty(1).kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		else if (_global_jazyk == JAZYK_HU){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;
				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.typslav_lokal = LOKAL_SLAV_SZEGED_CSAN_EGYH3;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_NOV_28_HU[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_HU;
		}// HU only

		break;

	case 29: // MES_NOV -- 29NOV

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))
			|| ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP))
			|| ((_global_jazyk == JAZYK_HU) && (_global_kalendar == KALENDAR_HU_OFM))
			){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				if (_global_jazyk == JAZYK_HU){
					set_popis_dummy();
				}

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_pc_1_8_15(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_set_zalmy_sviatok_sv_muzov(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_kcitresp_modl;

				break;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
			mystrcpy(_global_svaty1.meno, text_NOV_29_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ_VIACERI);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM, KALENDAR_CZ_OFMCAP, KALENDAR_HU_OFM

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // miestne povinné spomienky podľa miestneho kalendára; technicky 10, hoci podľa smerníc 11
			mystrcpy(_global_svaty1.meno, text_NOV_29_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	case 30: // MES_NOV -- 30NOV

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;
			_vlastna_cast_1citanie;
			_vlastna_cast_2citanie;

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_NOV_30[_global_jazyk], MENO_SVIATKU);
		if (_global_jazyk == JAZYK_SK){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_KOSICE_PATRON;
		}
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;
	};

	return pocet;
}// sviatky_svatych_11_november()

short int sviatky_svatych_12_december(short int den, short int poradie_svaty, _struct_sc sc){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;
	short int mesiac = MES_DEC;

	Log("mesiac december\n");
	switch (den){

	case 1: // MES_DEC -- 01DEC

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_DEC_01_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			mystrcpy(_global_svaty1.meno, text_DEC_01_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV, MODL_SPOL_CAST_DUCH_PAST_VIACERI);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_DEC_01_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK, MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_CERVENA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		break;

	case 2: // MES_DEC -- 02DEC // pôvodne sa slávilo pre český breviář "Svátek výročí posvěcení plzeňské katedrály"; upravené 2010-12-16: presunuté na 27. květen

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			else if (poradie_svaty == 2){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_DEC_02_1_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_DEC_02_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OFM

		if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OFMCAP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_DEC_02_2_OFM[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_CZ_OFMCAP

		break;

	case 3: // MES_DEC -- 03DEC

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SJ)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_INVITATORIUM;
				_vlastna_cast_antifona_inv;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_full(modlitba);

				modlitba = MODL_VESPERY;
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;
			}
			_global_svaty1.typslav = SLAV_SVIATOK;
			_global_svaty1.smer = 8; // miestne sviatky
			mystrcpy(_global_svaty1.meno, text_DEC_03_SJ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SJ

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_DEC_03[_global_jazyk], MENO_SVIATKU);
			if (_global_jazyk == JAZYK_SK){ // 2006-09-19: odvetvené len pre Slovensko
				_global_svaty1.typslav_lokal = LOKAL_SLAV_BYSTRICA_PATRON;
			}
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 4: // MES_DEC -- 04DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_04[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 5: // MES_DEC -- 05DEC

		if (((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_SDB)) || ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_SDB))){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				// _vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = (_global_jazyk == JAZYK_SK) ? LOKAL_SLAV_SVIATOK_VDB : LOKAL_SLAV_SVIATOK_VDB_CZ;
			mystrcpy(_global_svaty1.meno, text_DEC_05_SDB[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_SDB a KALENDAR_CZ_SDB

		break;

	case 6: // MES_DEC -- 06DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_06[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 7: // MES_DEC -- 07DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			if (_global_jazyk != JAZYK_CZ){ // 2009-12-08: pre cz nie je vlastný hymnus
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			if (_global_jazyk != JAZYK_CZ){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_DEC_07[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 8: // MES_DEC -- 08DEC

	label_8_DEC :

		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		if ((poradie_svaty == UNKNOWN_PORADIE_SVATEHO) || (poradie_svaty == 1)){
			// preto 0 -> UNKNOWN_PORADIE_SVATEHO, ze aj ked nie je svaty urceny, ide o slavnost, ktora ma takmer najvacsiu prioritu, a preto ma aj prve vespery - a vtedy by to normalne nefungovalo; nastavenie veci pre modlitbu by sa muselo diat v predoslom dni, co je neciste riesenie

			// definovanie parametrov pre modlitbu
			sc = _decode_spol_cast(_global_svaty1.spolcast);
			Log("08DEC | Neposkvrnene pocatie Panny Marie: sc: {%s, %s, %s}, svaty == %d\n\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3), poradie_svaty);

			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			if ((_global_jazyk != JAZYK_CZ) || (_global_jazyk != JAZYK_CZ_OP)){
				set_popis_dummy();
			}

			modlitba = MODL_PRVE_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_panien(modlitba);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_1nedele_rch();

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_marie(modlitba);

			if (_global_jazyk == JAZYK_CZ){
				_vlastna_cast_mcd_full;
			}
			else{
				_vlastna_cast_mcd_ant_kcitresp_modl;
			}

			// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
			if (_global_den.denvt != DEN_NEDELA) {
				_set_zalmy_mcd_doplnkova_psalmodia();
			}
			else {
				_set_zalmy_1nedele_mcd();
			}

			modlitba = MODL_VESPERY;
			_vlastna_cast_full(modlitba);
			_set_zalmy_sviatok_panien(modlitba);

			modlitba = MODL_PRVE_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			modlitba = MODL_KOMPLETORIUM;
			_set_kompletorium_slavnost(modlitba);

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){

				file_name_vlastny_kalendar(_global_kalendar);

				modlitba = MODL_PRVE_VESPERY;
				_vlastna_cast_kresponz;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_kresponz;
				_vlastna_cast_magnifikat;

			}// kalendár pre KALENDAR_SK_OP

			if ((_global_jazyk == JAZYK_CZ) && (_global_kalendar == KALENDAR_CZ_OPRAEM)){

				file_name_vlastny_kalendar(_global_kalendar);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_vlastna_cast_nunc_dimittis;

				modlitba = MODL_KOMPLETORIUM;
				_vlastna_cast_nunc_dimittis;

			}// kalendár pre KALENDAR_CZ_OPRAEM

			if (poradie_svaty != UNKNOWN_PORADIE_SVATEHO){
				break;
			}
		}
		_global_svaty1.typslav = SLAV_SLAVNOST;
		_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		_global_svaty1.prik = PRIKAZANY_SVIATOK;
		mystrcpy(_global_svaty1.meno, text_DEC_08[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 9: // MES_DEC -- 09DEC

		if (_global_den.denvt == DEN_PONDELOK){
			// t.j. slavnost neposkvrneneho pocatia P. Marie padla na nedelu
			sprintf(_anchor_head, "%02d%s_", den - 1, nazov_MES[mesiac]); // MES_DEC
			Log("  _anchor_head == %s\n", _anchor_head);
			Log("jumping to label_8_DEC...\n");
			goto label_8_DEC;
		}

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_09[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_SV_MUZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 11: // MES_DEC -- 11DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_11[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}

			pocet = 2;
			_global_svaty2.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty2.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty2.meno, text_DEC_11_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty2.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA, MODL_SPOL_CAST_SV_ZENA_REHOLNIK);
			_global_svaty2.farba = LIT_FARBA_BIELA;
			_global_svaty2.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

	// Sviatok Sv. Jany Františky de Chantal presunuty z 12. decembra na 12. augusta.

	case 12: // MES_DEC -- 12DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_modlitba;
			_vlastna_cast_2citanie;

			modlitba = MODL_VESPERY;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_12[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 13: // MES_DEC -- 13DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_benediktus;
			_vlastna_cast_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_2citanie;
			_vlastna_cast_modlitba;

			modlitba = MODL_VESPERY;
			_vlastna_cast_magnifikat;
			_vlastna_cast_modlitba;

			break;
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
		mystrcpy(_global_svaty1.meno, text_DEC_13[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENICA, MODL_SPOL_CAST_PANNA);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 14: // MES_DEC -- 14DEC

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_PRVE_VESPERY;
				_set_zalmy_ocd_jan_z_kriza(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_POSV_CITANIE;
				_set_zalmy_ocd_jan_z_kriza(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_RANNE_CHVALY;
				_set_zalmy_ocd_jan_z_kriza(modlitba);
				_vlastna_cast_full(modlitba);

				_vlastna_cast_mcd_ant_kcitresp_modl;

				// ak je modlitba cez deň na slávnosť, tak sa majú použiť žalmy z doplnkovej psalmódie
				if (_global_den.denvt != DEN_NEDELA) {
					_set_zalmy_mcd_doplnkova_psalmodia();
				}
				else {
					_set_zalmy_1nedele_mcd();
				}

				modlitba = MODL_VESPERY;
				_set_zalmy_ocd_jan_z_kriza(modlitba);
				_vlastna_cast_full(modlitba);

				modlitba = MODL_PRVE_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				modlitba = MODL_KOMPLETORIUM;
				_set_kompletorium_slavnost(modlitba);

				break;
			}
			_global_svaty1.typslav = SLAV_SLAVNOST;
			_global_svaty1.smer = 3; // slávnosti Pána, preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári // _global_svaty1.smer = 4; // miestne slávnosti podľa miestneho kalendára
			mystrcpy(_global_svaty1.meno, text_DEC_14_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEBRAT);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		else{
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_SPOMIENKA;
			_global_svaty1.smer = 10; // povinné spomienky podľa všeobecného kalendára
			mystrcpy(_global_svaty1.meno, text_DEC_14[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_UCITEL_CIRKVI); // 2010-12-16: zapoznámkované MODL_SPOL_CAST_DUCH_PAST_KNAZ; podľa breviára len spol. časť učiteľov Cirkvi
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		}// všeobecný kalendár

		break;

	case 16: // MES_DEC -- 16DEC

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OP)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			_global_svaty1.prik = VOLNA_LUBOVOLNA_SPOMIENKA; // ľubovoľná spomienka uvedená kurzívou bez popisu
			mystrcpy(_global_svaty1.meno, text_DEC_16_OP[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_SV_MUZ_REHOLNIK);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OP

		if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OCD)){
			if (poradie_svaty == 1){

				file_name_vlastny_kalendar(_global_kalendar);

				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie;
				_vlastna_cast_modlitba;

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;

				break;
			}
			_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
			_global_svaty1.smer = 12; // ľubovoľné spomienky
			mystrcpy(_global_svaty1.meno, text_DEC_16_OCD[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = _global_kalendar;
		}// kalendár pre KALENDAR_SK_OCD

		break;

// odtiaľto (od 17DEC) až do konca roka (31DEC) sú tzv. privilegované dni

	case 21: // MES_DEC -- 21DEC

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v advente v dňoch 17.-24. decembra)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_21[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ, MODL_SPOL_CAST_UCITEL_CIRKVI);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 22: // MES_DEC -- 22DEC

		if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
			if (poradie_svaty == 1){
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY){
					set_spolocna_cast(sc, poradie_svaty);
				}
				// všetko je zo spoločnej časti na výročie posviacky chrámu

				break;
			}
			_global_svaty1.smer = 11; // miestne povinné spomienky
			_global_svaty1.typslav_lokal = LOKAL_SLAV_CESKE_BUDEJOVICE;
			_global_svaty1.typslav = SLAV_SVIATOK;
			mystrcpy(_global_svaty1.meno, text_DEC_22_CZ[_global_jazyk], MENO_SVIATKU);
			_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_POSVIACKA_CHRAMU);
			_global_svaty1.farba = LIT_FARBA_BIELA;
			_global_svaty1.kalendar = KALENDAR_VSEOBECNY_CZ;
		}// CZ, CZOP only

		break;

	case 23: // MES_DEC -- 23DEC

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka v advente v dňoch 17.-24. decembra)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_23[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_KNAZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 26: // MES_DEC -- 26DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_prosieb(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full_okrem_prosieb(modlitba);

			_vlastna_cast_mcd_kcitresp_modl;

			// vespery -- vsetko je z oktavy narodenia Pana (okrem hymnu pre CZ k vlastnímu výběru)
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_DEC_26[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 27: // MES_DEC -- 27DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full_okrem_kresp(modlitba);

			_vlastna_cast_mcd_modlitba;

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			_vlastna_cast_antifony;
			// _vlastna_cast_kresponz; - zo sviatkov apoštolov
			_vlastna_cast_1citanie;
			_vlastna_cast_2citanie;
			_vlastna_cast_modlitba;
			_set_zalmy_sviatok_jana_ap(modlitba);

			// vespery -- vsetko je z oktavy narodenia Pana (okrem hymnu pre CZ k vlastnímu výběru)
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_DEC_27[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_APOSTOL);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_EGER_FOEGYH;
		}// HU only

		break;

	case 28: // MES_DEC -- 28DEC

		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);

			modlitba = MODL_INVITATORIUM;
			_vlastna_cast_antifona_inv;

			modlitba = MODL_RANNE_CHVALY;
			_vlastna_cast_full(modlitba);

			modlitba = MODL_POSV_CITANIE;
			_vlastna_cast_full_okrem_prosieb(modlitba);

			_vlastna_cast_mcd_kcitresp_modl;

			// vespery -- vsetko je z oktavy narodenia Pana (okrem hymnu pre CZ k vlastnímu výběru)
			if (je_CZ_hymny_k_volnemu_vyberu){
				_vlastna_cast_hymnus(modlitba, _global_den.litobd);
			}

			break;
		}
		_global_svaty1.typslav = SLAV_SVIATOK;
		_global_svaty1.smer = 7; // sviatky preblahoslavenej Panny Márie a svätých, uvedené vo všeobecnom kalendári
		mystrcpy(_global_svaty1.meno, text_DEC_28[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_VIAC_MUCENIKOV);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;

	case 29: // MES_DEC -- 29DEC

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka vo Vianočnej oktáve)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat;
				_vlastna_cast_modlitba;
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_29[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_BISKUP, MODL_SPOL_CAST_MUCENIK);
		_global_svaty1.farba = LIT_FARBA_CERVENA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;
		if (_global_jazyk == JAZYK_HU){
			_global_svaty1.typslav_lokal = LOKAL_SLAV_ESZTERGOM_EML;
		}// HU only

		break;

	case 31: // MES_DEC -- 31DEC

		if (poradie_svaty == 1){
			// na spomienku v privilegovaný deň (spomienka vo Vianočnej oktáve)
			if (je_privileg){
				if (query_type != PRM_DETAILY)
					set_popis_svaty_rch_mcd_pc_vesp(poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_VESPERY;
				_vlastna_cast_magnifikat_spomprivileg;
				_vlastna_cast_modlitba_spomprivileg;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_2citanie_spomprivileg;
				_vlastna_cast_modlitba;

			}// je_privileg
			else{
				// definovanie parametrov pre modlitbu
				if (query_type != PRM_DETAILY)
					set_spolocna_cast(sc, poradie_svaty);

				modlitba = MODL_RANNE_CHVALY;
				_vlastna_cast_benediktus;
				_vlastna_cast_modlitba;

				modlitba = MODL_POSV_CITANIE;
				_vlastna_cast_modlitba;
				_vlastna_cast_2citanie;

				// nema vespery, lebo uz su prve vespery slavnosti bohorodicky panny marie
			}// nie je_privileg

			break;
		}
		_global_svaty1.typslav = SLAV_LUB_SPOMIENKA;
		_global_svaty1.smer = 12; // ľubovoľné spomienky
		mystrcpy(_global_svaty1.meno, text_DEC_31[_global_jazyk], MENO_SVIATKU);
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_DUCH_PAST_PAPEZ);
		_global_svaty1.farba = LIT_FARBA_BIELA;
		_global_svaty1.kalendar = KALENDAR_VSEOBECNY;

		break;
	};

	return pocet;
}// sviatky_svatych_12_december()

short int sviatky_svatych(short int den, short int mesiac, short int poradie_svaty){
	// toto priradujeme preto, aby sme nemuseli pri kazdom svatom priradovat pocet = 1;
	short int pocet = 1;

	char _anchor_vlastne_slavenie[SMALL];

	Log("-- sviatky_svatych(%d, %d) -- zaciatok\n", den, mesiac);

	// nasledujuca pasaz v pripade, ze poradie_svaty nie je dane (t.j. nie je 1, 2 alebo 3) vycisti udaje; to je vtedy, ked je tato funkcia volana po prvykrat
	if ((poradie_svaty < 1) || (poradie_svaty > MAX_POCET_SVATY)){ // napr. aj UNKNOWN_PORADIE_SVATEHO
		for (short int i = 0; i < MAX_POCET_SVATY; i++){
			short int p = i + 1;
			// deň
			_global_svaty(p).den = den;
			// mesiac
			_global_svaty(p).mesiac = mesiac;
			// rok
			_global_svaty(p).rok = _global_den.rok;
			// denvt
			_global_svaty(p).denvt = _global_den.denvt;
			// denvr
			_global_svaty(p).denvr = _global_den.denvr;
			// smer
			_global_svaty(p).smer = _global_den.smer;
			// litobd
			_global_svaty(p).litobd = _global_den.litobd;
			// litrok
			_global_svaty(p).litrok = _global_den.litrok;
			// tyzden
			_global_svaty(p).tyzden = _global_den.tyzden;
			// tyzzal
			_global_svaty(p).tyzzal = _global_den.tyzzal;
			// typslav - neurcena
			_global_svaty(p).typslav = SLAV_NEURCENE;
			// typ lokálneho slávenia - neurčené; pridané 2005-07-27
			_global_svaty(p).typslav_lokal = LOKAL_SLAV_NEURCENE;
			// prik - nie je prikazany
			_global_svaty(p).prik = NIE_JE_PRIKAZANY_SVIATOK;
			// meno - neurcene
			mystrcpy(_global_svaty(p).meno, STR_EMPTY, MENO_SVIATKU);
			// spolcast - neurcena
			_global_svaty(p).spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA);
			Log("nastavil som _global_svaty(%d) na default (bud neurcene alebo z _global_den)\n", p);
			_global_svaty(p).farba = LIT_FARBA_NEURCENA;
			_global_svaty(p).kalendar = KALENDAR_NEURCENY;
			// nastavenie lc_str_id
			mystrcpy(_global_svaty(p).lc_str_id, STR_EMPTY, MAX_LC_STR_ID);
		}
	}

	Log("/* nastavenie nazvu suboru, kotvy apod. (sviatky_svatych) */\n");
	// nastavenie nazvu suboru, kotvy apod.

	if (poradie_svaty > 1){
		// pridame cislo svateho
		sprintf(_anchor_head, "%02d%s%d_", den, nazov_MES[mesiac - 1], poradie_svaty);
	}
	else{
		sprintf(_anchor_head, "%02d%s_", den, nazov_MES[mesiac - 1]);
	}
	Log("  _anchor_head == %s\n", _anchor_head);

	sprintf(_file, "sv_%s.htm", nazov_mes[mesiac - 1]);
	Log("  _file == %s\n", _file);

	// 2005-07-26: súbor pre posvätné čítania
	sprintf(_file_pc, "pc_sv_%s.htm", nazov_mes[mesiac - 1]);
	Log("  _file_pc == %s\n", _file_pc);

	// LOG_ciara_sv; Log("_global_den: \n"); Log(_global_den);

	// az teraz, ked je v _global_den (pri druhom volani fcie) spravna hodnota z _global_svaty[1,2,3], mozem urobit toto priradenie do sc
	_struct_sc sc = _decode_spol_cast(_global_den.spolcast);

	Log("\tDeklarujem štruktúru sc == ({%s, %s, %s}) -- begin\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3));

	LOG_ciara_sv;
	Log("Začiatok veľkého switch()-u podľa mesiacov a dní\nTeraz nasleduje veľký switch() podľa mesiacov a dní...\n");
	// a teraz velky switch()... 'Velky inkvizitor'... ;-)
	switch (mesiac - 1){
		case MES_JAN:
			pocet = sviatky_svatych_01_januar(den, poradie_svaty, sc);
			break; // case MES_JAN
		case MES_FEB:
			pocet = sviatky_svatych_02_februar(den, poradie_svaty, sc);
			break; // case MES_FEB
		case MES_MAR:
		case MES_APR:
			pocet = sviatky_svatych_03_marec_04_april(den, mesiac, poradie_svaty, sc);
			break; // case MES_MAR + case MES_APR
		case MES_MAY:
			pocet = sviatky_svatych_05_maj(den, poradie_svaty, sc);
			break; // case MES_MAY
		case MES_JUN:
			pocet = sviatky_svatych_06_jun(den, poradie_svaty, sc);
			break; // case MES_JUN
		case MES_JUL:
			pocet = sviatky_svatych_07_jul(den, poradie_svaty, sc);
			break; // case MES_JUL
		case MES_AUG:
			pocet = sviatky_svatych_08_august(den, poradie_svaty, sc);
			break; // case MES_AUG
		case MES_SEP:
			pocet = sviatky_svatych_09_september(den, poradie_svaty, sc);
			break; // case MES_SEP
		case MES_OCT:
			pocet = sviatky_svatych_10_oktober(den, poradie_svaty, sc);
			break; // case MES_OCT
		case MES_NOV:
			pocet = sviatky_svatych_11_november(den, poradie_svaty, sc);
			break; // case MES_NOV
		case MES_DEC:
			pocet = sviatky_svatych_12_december(den, poradie_svaty, sc);
			break; // case MES_DEC
	}// switch(mesiac - 1)
	Log("Koniec veľkého switch()-u podľa mesiacov a dní.\n");
	LOG_ciara_sv;

	// pasaz pre spomienku neposkvrneneho srdca panny marie
	if ((_global_den.denvr == SRDPM) &&
		(_global_svaty1.smer >= 10)){
		// neposkvrneneho srdca panny marie | "berie sa v takom pripade, ked nie je slavenie s vyssou prioritou, teda smer < 10"
		Log(" neposkvrneneho srdca panny marie: \n");
		Log(" ...berie sa len v takom pripade, ked to nekoliduje\n");
		Log(" ...so slavenim, co ma vyssiu prioritu (smer < 10)\n");

		poradie_svaty = 1;
		if (poradie_svaty == 1){
			// definovanie parametrov pre modlitbu
			if (query_type != PRM_DETAILY)
				set_spolocna_cast(sc, poradie_svaty);
			// ZNOVUNASTAVENIE_POPISU_NA_DUMMY, 2003-06-30; 2009-06-10: zapoznámkované | 2012-06-18: opätovne odpoznámkované, lebo 16.06.2012 tam dalo pre MCD popis (sk) 16JUN_POPIS
			Log("vo funkcii sviatky_svatych() spustam set_popis_dummy(); - kvoli spomienke neposkvrneneho srdca panny marie...\n");
			set_popis_dummy();
			Log("set_popis_dummy() skoncila.\n");

			mystrcpy(_file, FILE_SRDCA_PM, MAX_STR_AF_FILE);
			mystrcpy(_anchor, ANCHOR_SRDCA_PM, MAX_STR_AF_ANCHOR);
			mystrcpy(_anchor_vlastne_slavenie, ANCHOR_SRDCA_PM, MAX_STR_AF_ANCHOR);
			Log("  ide o spomienku srdca panny marie: _file = `%s', _anchor = %s...\n", _file, _anchor);

			modlitba = MODL_RANNE_CHVALY;
			_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
			_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
			// popis má len pre CZ; 2013-02-04: upravené
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
			}

			modlitba = MODL_POSV_CITANIE;
			_srdca_pm_2cit;
			_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);
			// popis má len pre CZ; 2013-02-04: upravené
			if ((_global_jazyk == JAZYK_CZ) || (_global_jazyk == JAZYK_CZ_OP)){
				_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
			}

			if ((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM)){
				// 2011-03-21: doplnené pre OFM

				// najprv z vlastnej časti (všeobecnej) nastavíme aj modlitbu pre mcd
				modlitba = MODL_PREDPOLUDNIM;
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

				modlitba = MODL_NAPOLUDNIE;
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

				modlitba = MODL_POPOLUDNI;
				_vlastne_slavenie_modlitba(_anchor_vlastne_slavenie);

				// teraz z vlastnej časti (OFM proprium) nastavíme ostatné časti modlitieb
				file_name_vlastny_kalendar(_global_kalendar);

				modlitba = MODL_INVITATORIUM;
				_vlastne_slavenie_invitat(_anchor_vlastne_slavenie);

				modlitba = MODL_POSV_CITANIE;
				// popis má len pre CZ; 2013-02-04: upravené
				_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, _global_den.litobd);
				_vlastne_slavenie_1citanie(_anchor_vlastne_slavenie);
				_set_zalmy_sviatok_marie(modlitba);
				// ToDo: ešte nastaviť antifóny zo spoločnej časti na sviatky Panny Márie...

				modlitba = MODL_RANNE_CHVALY;
				_vlastne_slavenie_popis(_anchor_vlastne_slavenie);
				_vlastne_slavenie_hymnus(modlitba, _anchor_vlastne_slavenie, _global_den.litobd);
				_vlastne_slavenie_antifony(_anchor_vlastne_slavenie);
				_set_zalmy_1nedele_rch();
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);
				_vlastne_slavenie_benediktus(_anchor_vlastne_slavenie);
				_vlastne_slavenie_prosby(_anchor_vlastne_slavenie);

				modlitba = MODL_PREDPOLUDNIM;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);

				modlitba = MODL_NAPOLUDNIE;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);

				modlitba = MODL_POPOLUDNI;
				_vlastne_slavenie_kcitanie(_anchor_vlastne_slavenie);
				_vlastne_slavenie_kresponz(_anchor_vlastne_slavenie);

				_global_svaty1.kalendar = _global_kalendar;
				_global_svaty1.typslav_lokal = LOKAL_SLAV_SVIATOK_OFMCAP;
				mystrcpy(_global_svaty1.meno, text_NEPOSKVRNENEHO_SRDCA_PM_OFM[_global_jazyk], MENO_SVIATKU);
			}
		}
		_global_svaty1.typslav = SLAV_SPOMIENKA;
		_global_svaty1.smer = 10;
		if (!((_global_jazyk == JAZYK_SK) && (_global_kalendar == KALENDAR_SK_OFM))){
			mystrcpy(_global_svaty1.meno, text_NEPOSKVRNENEHO_SRDCA_PM[_global_jazyk], MENO_SVIATKU);
		}
		_global_svaty1.spolcast = _encode_spol_cast(MODL_SPOL_CAST_PANNA_MARIA);
		// nastavenie lc_str_id pre spomienku Nepoškvrneného Srdca Panny Márie
		mystrcpy(_global_svaty1.lc_str_id, "10V6", MAX_LC_STR_ID);
	}// srdca panny marie

	if (_global_svaty1.typslav == SLAV_NEURCENE){
		Log("neurcene slavenie, t.j. pocet = 0\n");
		pocet = 0;
	}
	else{
		Log("slávenie je určené, počet == %d\n", pocet);
		Log("\tštruktúra sc == ({%s, %s, %s})\n", nazov_spolc(sc.a1), nazov_spolc(sc.a2), nazov_spolc(sc.a3));

		for (short int i = 0; i < MAX_POCET_SVATY; i++){
			if (pocet > i){
				Log(_global_svaty(i + 1));
				_global_svaty(i + 1).den = den;
				_global_svaty(i + 1).mesiac = mesiac;
				Log("  %d. %d: %s (typslav = %d) [smer = %d]\n", _global_svaty(i + 1).den, _global_svaty(i + 1).mesiac, _global_svaty(i + 1).meno, _global_svaty(i + 1).typslav, _global_svaty(i + 1).smer);
				// 2014-03-21: nastavenie lc_str_id pre sviatky svätých
				sprintf(_global_svaty(i + 1).lc_str_id, "%d.%d.", den, mesiac);
			}
		}
	}
	Log("-- sviatky_svatych(%d, %d) -- koniec (returning %d)\n", den, mesiac, pocet);
	return pocet;
}// sviatky_svatych(); -- 3 vstupy

short int sviatky_svatych(short int den, short int mesiac){
	short int ret;
	Log("-- sviatky_svatych(%d, %d) -- spustam bez tretieho parametra\n", den, mesiac);
	Log("   (poradie_svaty == UNKNOWN_PORADIE_SVATEHO [%d])\n", UNKNOWN_PORADIE_SVATEHO);
	ret = sviatky_svatych(den, mesiac, UNKNOWN_PORADIE_SVATEHO);
	Log("-- sviatky_svatych(%d, %d) -- spustene bez tretieho parametra, vysledok (pocet svatych) == %d\n", den, mesiac, ret);
	return ret;
}// sviatky_svatych(); -- 2 vstupy

short int sviatky_svatych(short int den, short int mesiac, short int poradie_svaty, short int druhykrat){
	short int ret;
	Log("-- sviatky_svatych(%d, %d, %d) -- spustam druhykrat\n", den, mesiac, poradie_svaty);
	if (druhykrat != 2){
		Log("   zle spustena, nie s 4. parametrom == 2\n");
		Log("-- sviatky_svatych(%d, %d) -- failure. Nespustila sa.\n");
		return 5;
	}

	Log("_global_svaty[1...%d] som nemenil, lebo poradie_svaty == %d\n", MAX_POCET_SVATY, poradie_svaty);
	Log("teraz priradim do _global_den vsetko z _global_svaty(%d)...\n", poradie_svaty);
	Log("    (tato cast bola povodne v sviatky_svatych s 3 vstupmi, ale teraz je tu)\n");
	if ((poradie_svaty > 0) && (poradie_svaty < PORADIE_PM_SOBOTA)){
		// 0: všetko je nastavené v _global_den
		_global_den = _global_svaty(poradie_svaty);
		// PORADIE_PM_SOBOTA: všetko je nastavené v _global_pm_sobota;
	}
	Log("takze _global_den teraz:\n");
	Log(_global_den);

	// az teraz, ked je v _global_den (pri druhom volani fcie) spravna hodnota z _global_svaty[1,2,3], mozem urobit toto priradenie do sc
	_struct_sc sc = _decode_spol_cast(_global_den.spolcast);

	Log("a hned nastavujem _global_opt[OPT_3_SPOLOCNA_CAST] (ak je neurčené: je teraz %d) na sc.a1):\n", _global_opt[OPT_3_SPOLOCNA_CAST]);
	// ak opt_3 je MODL_SPOL_CAST_NEURCENA, tak ju urcime podla 1. spolocnej casti
	if (_global_opt[OPT_3_SPOLOCNA_CAST] == MODL_SPOL_CAST_NEURCENA){
		_global_opt[OPT_3_SPOLOCNA_CAST] = sc.a1;
		Log("setting _global_opt[OPT_3_SPOLOCNA_CAST] to sc.a1 == %d\n", sc.a1);
	}
	else {
		Log("nie je potrebné modifikovať, lebo už je nastavená (hoci sc.a1 == %d)\n", sc.a1);
	}
	ret = sviatky_svatych(den, mesiac, poradie_svaty);
	Log("-- sviatky_svatych(%d, %d) -- spustene druhykrat, vysledok (pocet svatych) == %d\n", den, mesiac, ret);
	return ret;
}// sviatky_svatych(); -- 4 vstupy; posledny == 2

#endif // __KALENDAR_CPP_

