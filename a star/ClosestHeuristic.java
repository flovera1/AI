/**
 * Euclidean Heuristic: 
 * The tile that is closest to the target
 * as the next best tile.
 * Thu 5 Mar
 * @Caracas
 * @Fernando
 */
import org.newdawn.slick.util.pathfinding.AStarHeuristic;
import org.newdawn.slick.util.pathfinding.Mover;
import org.newdawn.slick.util.pathfinding.TileBasedMap;
public class ClosestHeuristic implements AStarHeuristic {
	public float getCost(TileBasedMap map, Mover mover, int x, int y, int tx, int ty) {		
		float dx     = tx - x;
		float dy     = ty - y;
		float result = (float) (Math.sqrt((dx*dx)+(dy*dy)));
		return result;
	}

}