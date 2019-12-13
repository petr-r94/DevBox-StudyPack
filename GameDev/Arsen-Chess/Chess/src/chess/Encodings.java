package chess;

import java.io.Serializable;

abstract public class Encodings {
	
	/**
	 * Перечисление, описывающее цвета фигур и игроков
	 */
	public enum Color implements Serializable {
		NONE("None", 2, 0) {

			@Override
			public int getAbsoluteX(int x, int y) {
				return 0;
			}

			@Override
			public int getAbsoluteY(int x, int y) {
				return 0;
			}
		},
		WHITE("White", 0, 1) {
			
			@Override
			public int getAbsoluteX(int x, int y) {
				return x;
			}

			@Override
			public int getAbsoluteY(int x, int y) {
				return y;
			}
			
		},
		GREEN("Green", 1, 2) {

			@Override
			public int getAbsoluteX(int x, int y) {
				return y;
			}

			@Override
			public int getAbsoluteY(int x, int y) {
				return -x;
			}
			
		},
		BLACK("Black", 0, 3) {

			@Override
			public int getAbsoluteX(int x, int y) {
				return -x;
			}

			@Override
			public int getAbsoluteY(int x, int y) {
				return -y;
			}
			
		},
		BLUE("Blue", 1, 4) {

			@Override
			public int getAbsoluteX(int x, int y) {
				return -y;
			}

			@Override
			public int getAbsoluteY(int x, int y) {
				return x;
			}
			
		};
		
		public final String name;
		public final int team;
		public final int colorCode;
		
		Color(String name, int team, int colorCode) {
			this.name = name;
			this.team = team;
			this.colorCode = colorCode;
		}
		
		/**
		 * Вычисляет абсолютную координату x из координат в системе данного
		 * цвета
		 */
		public abstract int getAbsoluteX(int x, int y);
		/**
		 * Вычисляет абсолютную координату y из координат в системе данного
		 * цвета
		 */
		public abstract int getAbsoluteY(int x, int y);
		
		public static final Color values[] = values();
		
		@Override
		public String toString() {
			return Integer.toString(this.ordinal());
		}
		
		
		public static Color fromString(String s) {
			return values[Integer.parseInt(s)];
		}
		
	}
	
	public enum Command {
		CHECK,
		SET_COLOR,
		SET_READY,
		NAME,
		MAKE_MOVE;
		public static final Command values[] = values();
		
		public static Command parseInt(int i) {
			return values[i];
		}
				
	}
	
	public enum Answer {
		SUCCEED,
		FAILED,
		STATUS;
		public static final Answer values[] = values();
		
		public static Answer parseInt(int i) {
			return values[i];
		}
		
	}
	
}
