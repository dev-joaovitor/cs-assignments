package src;

import src.game.Game;
import src.game.config.Config;
import src.game.io.IO;

public class Run {
    public static void main(String[] args) {
        Config cfg = Config.generate();
        IO.enableLogs = cfg.enableLogs;

        Game game = new Game(cfg);
        game.start();
        game.end();
    }
}
