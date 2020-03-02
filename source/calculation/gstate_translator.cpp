#include "gstate_translator.h"

namespace blaengine::calculation {

GameState GSateTranslator::interpretAndSetFen(string fen) {
  GameStateController gstate_controller = GameStateController();
  GameState& current_gstate = gstate_controller.current_game_state;

  validateFenString(fen);

  string fen_position = fen.substr(0, fen.find(WHITE_SPACE));
  gstate_controller.extractFenPosition(fen_position);

  fen.erase(0, fen.find(WHITE_SPACE) + 1);
  current_gstate.next_turn =
      (fen[0] == W_FOR_WHITE) ? Color::white : Color::black;

  fen.erase(0, fen.find(WHITE_SPACE) + 1);
  string castling_info = fen.substr(0, fen.find(WHITE_SPACE));
  if (castling_info.compare(DEFAULT_HYPHEN) != 0) {
    gstate_controller.extractFenCastling(castling_info);
  }

  fen.erase(0, fen.find(WHITE_SPACE) + 1);
  string en_passant = fen.substr(0, fen.find(WHITE_SPACE));
  if (en_passant[0] != (char&)DEFAULT_HYPHEN) {
    current_gstate.en_passant_field =
        gstate_controller.getFieldIndex(en_passant);
  }

  fen.erase(0, fen.find(WHITE_SPACE) + 1);
  string rule_40_moves = fen.substr(0, fen.find(WHITE_SPACE));
  current_gstate.half_moves_for_draw = std::stoi(rule_40_moves);

  fen.erase(0, fen.find(WHITE_SPACE) + 1);
  string next_full_move = fen.substr(0, fen.find(WHITE_SPACE));
  current_gstate.next_half_move += std::stoi(next_full_move) * 2;
  if (current_gstate.next_turn == Color::white) {
    current_gstate.next_half_move--;
  }

  return current_gstate;
}

GameState GSateTranslator::makeMovesFromFieldStrings(GameState game_state,
                                                     vector<string> moves) {
  GameStateController gstate_controller = GameStateController();
  gstate_controller.current_game_state = game_state;

  for (uint i = 0; i < moves.size(); i++) {
    validateMoveString(moves[i]);

    string field_string_before = moves[i].substr(0, 2);
    string field_string_after = moves[i].substr(2, 3);

    ushort field_before = gstate_controller.getFieldIndex(field_string_before);
    ushort field_after = gstate_controller.getFieldIndex(field_string_after);

    Piece piece_got = gstate_controller.transformPiece(moves[i]);
    gstate_controller.makeMove(field_before, field_after, piece_got);
  }

  return gstate_controller.current_game_state;
}

void GSateTranslator::validateFenString(string fen) {
  if (fen.empty()) {
    throw("FEN string was not in the right format or even empty.");
  }
}

void GSateTranslator::validateMoveString(string move) {
  if (move.empty() || move.size() < 4) {
    throw("move was in a wrong format. It has to be e.g. e2e3");
  }
}

}  // namespace blaengine::calculation