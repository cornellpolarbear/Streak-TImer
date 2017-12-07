open Graphics;;
open Model;;

Graphics.open_graph " 1000x1000";;

set_color black;;
(*)
let current_color : color = black;
  let switch_color (current:color) : color =
    match current with
    | black -> Color.red
    | red -> black
    | _ -> black
  *)
(*fill_rect 100 100 100 100;;*)

for i = 0 to 3 do
  for k = 0 to 3 do
    fill_rect (i*160 + 80) (k*160 + 80) 80 80;
    fill_rect (i*160 + 160) ((k*160)+160) 80 80
  done;
  (*  for j = 0 to 3 do
    fill_rect (i*200 + 200) ((j*200)+100) 100 100
  done;
      set_color black;
  *)
  done;;

set_color red;;
for i = 0 to 7 do
  moveto (i*80 + 80) (240);
  draw_char 'P';
  moveto (i*80 + 80) (560);
  draw_char 'P'
done;

(*Normal, Check, Checkmate, or Stalemate*)
type game_state = Normal | Check | Checkmate | Stalemate

(*this should be self-explanatory*)
type piece_type = Pawn | Knight | Bishop | Rook | Queen | King

(*Black or White*)
type player = Black | White

(*Contains the necessary information to identify a piece*)
type piece = piece_type * player

(*Identifies a space on a board*)
type space = char * int

(*Record containing the locations of all pieces, the current turn, the state as
  normal, check, checkmate, or stalemate and the previous state*)
type state = {
  current_player: player;
  game_state: game_state;
  locations: (piece * space) list;
  turns: int;
  previous_state: state option;
}

(*List of all pieces in the game*)
let pieces =
  [(Rook, White); (Knight, White); (Bishop, White);
   (Queen, White); (King, White); (Bishop, White);
   (Knight, White); (Rook, White); (Pawn, White);
   (Pawn, White); (Pawn, White); (Pawn, White);
   (Pawn, White); (Pawn, White); (Pawn, White);
   (Pawn, White); (Pawn, Black); (Pawn, Black);
   (Pawn, Black); (Pawn, Black); (Pawn, Black);
   (Pawn, Black);(Pawn, Black); (Pawn, Black);
   (Rook, Black); (Knight, Black); (Bishop, Black);
   (Queen, Black); (King, Black); (Bishop, Black);
   (Knight, Black); (Rook, Black)]
(*The initial locations of all the pieces on the board*)
let init_locations =
  [(Rook, White),('A',1); (Knight, White),('B',1); (Bishop, White),('C',1);
   (Queen, White),('D',1); (King, White),('E',1); (Bishop, White),('F',1);
   (Knight, White),('G',1); (Rook, White),('H',1); (Pawn, White),('A',2);
   (Pawn, White),('B',2); (Pawn, White),('C',2); (Pawn, White),('D',2);
   (Pawn, White),('E',2); (Pawn, White),('F',2); (Pawn, White),('G',2);
   (Pawn, White),('H',2); (Pawn, Black),('A',7); (Pawn, Black),('B',7);
   (Pawn, Black),('C',7); (Pawn, Black),('D',7); (Pawn, Black),('E',7);
   (Pawn, Black),('F',7); (Pawn, Black),('G',7); (Pawn, Black),('H',7);
   (Rook, Black),('A',8); (Knight, Black),('B',8); (Bishop, Black),('C',8);
   (Queen, Black),('D',8); (King, Black),('E',8); (Bishop, Black),('F',8);
   (Knight, Black),('G',8); (Rook, Black),('H',8)]

let init_state = {
  current_player = White;
  game_state = Normal;
  locations = init_locations;
  turns = 0;
  previous_state = None;
}

let init_state = {
    current_player = White;
    game_state = Normal;
    locations = init_locations;
    turns = 0;
    previous_state = None;
  };

  let convert_letter_to_coordinates (chr:char) = match chr with
    | 'A' -> 80
    | 'B' -> 160
    | 'C' -> 240
    | 'D' -> 320
    | 'E' -> 400
    | 'F' -> 480
    | 'G' -> 560
    | _ -> 9;

let convert_number_to_coordinates i =
  if (i < 9) && (i > 0) then i*80
  else failwith "Not valid space";




    (*  let draw_piece locations =*)
