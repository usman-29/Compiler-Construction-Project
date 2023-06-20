#pragma once

#include "token.h"



bool E_noman();
bool T_noman();
bool E_noman();
bool U_noman();
bool V_noman();
bool W_noman();
bool X_noman();
bool Y_noman();
bool Z_noman();
bool statement_list();



bool Z_noman() {

	nkt = getToken();
	if (nkt.token == DIGIT)
	{
		return true;
	}
	else if (nkt.token == IDENTIFIER)
	{
		return true;
	}
	else if (nkt.token == LEFTBRACKET)
	{
		if (E_noman())
		{
			nkt = getToken();
			if (nkt.token == RIGHTBRACKET)
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

bool Y_noman() {

	do {
		if (Z_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == MULTIPLY || nkt.token == DIVID || nkt.token == REMAINDER);
	ungetToken();
	return true;
}

bool X_noman() {

	do {
		if (Y_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == ADD || nkt.token == MINUS);
	ungetToken();
	return true;
}

bool W_noman() {

	do {
		if (X_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == SHIFTLEFT || nkt.token == SHIFTRIGHT);
	ungetToken();
	return true;
}

bool V_noman() {

	do {
		if (W_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == LESSTHAN || nkt.token == LESSOREQUAL || nkt.token == GREATER || nkt.token == GREATEROREQUAL);
	ungetToken();
	return true;
}

bool U_noman() {

	do {
		if (V_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == ASSIGNMENT || nkt.token == NOTEQUAL);
	ungetToken();
	return true;
}

bool T_noman() {

	do {
		if (U_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == LOGICALAND);
	ungetToken();
	return true;
}

bool E_noman() {

	do {
		if (T_noman()) {
			nkt = getToken();
		}
		else {
			return false;
		}

	} while (nkt.token == OR);
	ungetToken();
	return true;
}





bool assignment() {
	nkt = getToken();
	if (nkt.token == IDENTIFIER) {
		nkt = getToken();
		if (nkt.token == EQUAL || nkt.token == PLUSEQUAL || nkt.token == MINUSEQUAL || nkt.token == MINUS || nkt.token == ADD) {
			if (E_noman()) {
				nkt = getToken();
				if (nkt.token == SEMICOLON) {
					return true;
				}

			}
		}
	}
	else if (nkt.token == IF) {
		nkt = getToken();
		if (nkt.token == LEFTBRACKET) {
			if (E_noman()) {
				nkt = getToken();
				if (nkt.token == RIGHTBRACKET) {
					nkt = getToken();
					if (nkt.token == LEFTCURLYBRACKET) {
						if (statement_list()) {
							nkt = getToken();
							if (nkt.token == RIGHTCURLYBRACKET) {
								nkt = getToken();
								if (nkt.token != ELSE) {
									ungetToken();
									return true;
								}
								else {
									nkt = getToken();
									if (nkt.token == LEFTCURLYBRACKET) {
										if (statement_list()) {
											nkt = getToken();
											if (nkt.token == RIGHTCURLYBRACKET) {
												return true;
											}
										}
									}
								}
							}
						}
						else {
							nkt = getToken();
							if (nkt.token == RIGHTCURLYBRACKET) {
								nkt = getToken();
								if (nkt.token != ELSE) {
									ungetToken();
									return true;
								}
								else {
									nkt = getToken();
									if (nkt.token == LEFTCURLYBRACKET) {
										if (statement_list()) {
											nkt = getToken();
											if (nkt.token == RIGHTCURLYBRACKET) {
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (nkt.token == DO) {
		nkt = getToken();
		if (nkt.token == LEFTCURLYBRACKET) {
			if (statement_list()) {
				nkt = getToken();
				if (nkt.token == RIGHTCURLYBRACKET) {
					nkt = getToken();
					if (nkt.token == WHILE) {
						nkt = getToken();
						if (nkt.token == LEFTBRACKET) {
							if (E_noman()) {
								nkt = getToken();
								if (nkt.token == RIGHTBRACKET) {
									nkt = getToken();
									if (nkt.token == SEMICOLON) {
										return true;
									}
								}
							}
						}
					}
				}
			}
			else {
				nkt = getToken();
				if (nkt.token == RIGHTCURLYBRACKET) {
					nkt = getToken();
					if (nkt.token == WHILE) {
						nkt = getToken();
						if (nkt.token == LEFTBRACKET) {
							if (E_noman()) {
								nkt = getToken();
								if (nkt.token == RIGHTBRACKET) {
									nkt = getToken();
									if (nkt.token == SEMICOLON) {
										return true;
									}
								}
							}
						}
					}
				}

			}
		}
	}
	else {
		if (nkt.token == WHILE) {
			nkt = getToken();
			if (nkt.token == LEFTBRACKET) {
				if (E_noman()) {
					nkt = getToken();
					if (nkt.token == RIGHTBRACKET) {
						nkt = getToken();
						if (nkt.token == LEFTCURLYBRACKET) {
							if (statement_list()) {
								nkt = getToken();
								if (nkt.token == RIGHTCURLYBRACKET) {
									return true;
								}
							}
							else {
								nkt = getToken();
								if (nkt.token == RIGHTBRACKET) {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}


bool statement() {
	if (assignment()) {
		return true;
	}

	return false;
}



bool statement_list()  // statement list 
{

	if (statement())
	{
		do
		{
			nkt = getToken();
			if (nkt.token == IF || nkt.token == DO || nkt.token == IDENTIFIER)
			{
				ungetToken();
				if (!statement())
					return false;
			}
			else
			{
				ungetToken();
				break;
			}

		} while (1);
		return true;
	}
	return false;

}




bool program() {
	nkt = getToken();
	if (nkt.token == BEGIN) {
		if (statement_list()) {
			nkt = getToken();
			if (nkt.token == END) {
				return true;
			}
		}
	}
	else {
		ungetToken();
		return false;
	}
}



