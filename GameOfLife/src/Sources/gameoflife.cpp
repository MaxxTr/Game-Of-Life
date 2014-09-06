#include "../Headers/gameoflife.h"

const QString GameOfLife::m_helpText = 
	QString("<b>Game Overview</b>").append( 
	new QString("<br>This game simulates predators-preys relations.")).append( 
	new QString("<br>Prey life cycle based on Game of Life rules with possibility to bring successors.")).append( 
	new QString("<br>Predators could and need to eat preys and bring successors.")).append( 
	new QString("<br>All creatures have startup parameters that could mutate during reproduction.")).append( 
	new QString("<br>Predators colored red, current life cycle's predator's successors colored blue. Omnivorous predators colored yellow.")).append( 
	new QString(" Preys colored green. <br> Prey's and predator's <a href=\"http://en.wikipedia.org/wiki/Black_swan_theory\">\"Black Swan\"</a> individuals colored black.")).append(
	new QString("<br>Black Swan individuals cause to all other creatures from the same kind around try to be as close as possible to the Black Swan.")).append(
	new QString(" They move on the board by dynamic equal(<a href=\"http://en.wikipedia.org/wiki/Chaos_theory\">\"Chaos Theory\"</a>) so that gives additional level of randomization.")).append(
	new QString("<br>Different predator's clans(each setup is a new clan) could be in peace or in war state, defined randomly.")).append(
	new QString("<br>Each creature have randomly defined life target (reproduction, safety, food, random, singleness).")).append(
	new QString("<br>There is probability to omnivorous predator's individual.")).append(
	new QString("<br><br><b>Game Control</b>")).append(
	new QString("<br>To set up predators: press right mouse button on the board and move mouse to set area.")).append(
	new QString("<br>To set up preys: press left mouse button on the board and move mouse to set area.")).append( 
	new QString("<br>To increase saturation: when the mouse's button pressed rotate wheel.")).append( 
	new QString("<br>You can control width and height of the board.")).append( 
	new QString("<br>Start simulation(Start button), run simulation cycles one by one(Next Iteration),")).append( 
	new QString("<br>Pause simulation(Pause) and stop current simulation with board cleaning(Stop).")).append( 
	new QString("<br>Show simulation run time information( Run Time Info button).")).append( 
	new QString("<br><br><b>Developer</b>")).append(
	new QString("<br><a href=\"mailto:max.trosman@gmail.com\">Max Trosman</a>")).append(
	new QString("<br>Copyright \xA9 All Rights Reseved."));