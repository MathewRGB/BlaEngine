#include "calculator.h"

namespace blaengine::calculation {

Calculator::Calculator() {
  this->game_state_controller = GameStateController();
}

Calculator::~Calculator() {}

void Calculator::interpretAndSetFen(string fen) {
  this->validateFenString(fen);

  string fen_position = fen.substr(0, fen.find(" "));
  this->game_state_controller.extractFenPosition(fen_position);

  fen.erase(0, fen.find(" ") + 1);
  this->game_state_controller.current_game_state.next_turn =
      (fen[0] == 'w') ? NextTurn::white : NextTurn::black;

  fen.erase(0, fen.find(" ") + 1);
  string castling_info = fen.substr(0, fen.find(" "));
  if (castling_info.compare("-") != 0) {
    this->game_state_controller.extractFenCastling(castling_info);
  }

  fen.erase(0, fen.find(" ") + 1);
  string en_passant = fen.substr(0, fen.find(" "));
  if (en_passant[0] != '-') {
    this->game_state_controller.current_game_state.en_passant_field =
        this->game_state_controller.getFieldIndex(en_passant);
  }

  fen.erase(0, fen.find(" ") + 1);
  string rule_40_moves = fen.substr(0, fen.find(" "));
  this->game_state_controller.current_game_state.half_moves_for_draw =
      std::stoi(rule_40_moves);

  fen.erase(0, fen.find(" ") + 1);
  string next_full_move = fen.substr(0, fen.find(" "));
  this->game_state_controller.current_game_state.next_half_move +=
      std::stoi(next_full_move) * 2;
  if (this->game_state_controller.current_game_state.next_turn ==
      NextTurn::white) {
    this->game_state_controller.current_game_state.next_half_move--;
  }
}

void Calculator::makeMovesFromFieldStrings(vector<string> moves) {
  for (uint i = 0; i < moves.size(); i++) {
    this->validateMoveString(moves[i]);
    ushort field_before =
        this->game_state_controller.getFieldIndex(moves[i].substr(0, 2));
    ushort field_after =
        this->game_state_controller.getFieldIndex(moves[i].substr(2, 3));

    // TODO function for this needed piece transformation
    Pieces piece_got = (moves[i].length() == 5) ? (Pieces)(moves[i].at(4))
                                                : Pieces::left_piece;
    if (piece_got == Pieces::black_queen &&
        this->game_state_controller.current_game_state.next_turn ==
            NextTurn::white) {
      piece_got = Pieces::white_queen;
    }
    if (piece_got == Pieces::black_knight &&
        this->game_state_controller.current_game_state.next_turn ==
            NextTurn::white) {
      piece_got = Pieces::white_knight;
    }
    if (piece_got == Pieces::black_rook &&
        this->game_state_controller.current_game_state.next_turn ==
            NextTurn::white) {
      piece_got = Pieces::white_rook;
    }
    if (piece_got == Pieces::black_bishop &&
        this->game_state_controller.current_game_state.next_turn ==
            NextTurn::white) {
      piece_got = Pieces::white_bishop;
    }

    this->game_state_controller.makeMove(field_before, field_after, piece_got);

    this->game_state_controller.current_game_state.next_half_move++;
    this->game_state_controller.current_game_state.next_turn =
        (this->game_state_controller.current_game_state.next_turn ==
         NextTurn::white)
            ? NextTurn::black
            : NextTurn::white;
  }
}

void Calculator::validateFenString(string fen) {
  if (fen.empty()) {
    throw("FEN string was not in the right format or even empty.");
  }
}

void Calculator::validateMoveString(string move) {
  if (move.empty() || move.size() < 4) {
    throw("move was in a wrong format. It has to be e.g. e2e3");
  }
}

}  // namespace blaengine::calculation