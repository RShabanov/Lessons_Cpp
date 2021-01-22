#pragma once


enum class game_exception : int {
	CANNOT_OPEN_FILE = 0,
	BAD_FILE
};


static const char* errors[]{
	"file cannot be opened.",
	"bad file."
};


class GameException {
	game_exception error_type;
public:
	GameException(game_exception _type)
		: error_type(_type) {}

	const char* what() const { return errors[int(error_type)]; }
};

