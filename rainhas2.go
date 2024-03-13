package main

import "fmt"

const LINE int = 8
const COLUMN int = 8

var heuristics = make(map[string]int)

func createMatrix(matrix *[][]int) {
	for i := 0; i < COLUMN; i++ {
		(*matrix)[i] = make([]int, COLUMN)
	}

	for i := 0; i < LINE; i++ {
		for j := 0; j < COLUMN; j++ {
			(*matrix)[i][j] = 0
		}
	}
}

func printMatrix(m *[][]int) {
	for i := 0; i < LINE; i++ {
		for j := 0; j < COLUMN; j++ {
			fmt.Print((*m)[i][j], " ")
		}
		fmt.Println()
	}
}

func checkColumn(matrix *[][]int, posX int) {
	validator := false
	for j := 0; j < COLUMN; j++ {
		if (*matrix)[posX][j] == 8 {
			validator = true
		}
	}

	if validator {
		for j := 0; j < COLUMN; j++ {
			if (*matrix)[posX][j] != 8 {
				(*matrix)[posX][j] = 1
			}
		}
	}
}

func checkLine(matrix *[][]int, posY int) {
	validator := false
	for j := 0; j < LINE; j++ {
		if (*matrix)[j][posY] == 8 {
			validator = true
		}
	}

	if validator {
		for j := 0; j < LINE; j++ {
			if (*matrix)[j][posY] != 8 {
				(*matrix)[j][posY] = 1
			}
		}
	}

}

func checkDiagonal(matrix *[][]int, posX, posY int) {
	validator := false
	refMain := posX - posY
	//sum := refMain + 2
	for i := 0; i < LINE; i++ {
		for j := 0; j < COLUMN; j++ {
			if (refMain == (i-j) && (*matrix)[i][j] == 8) || (posX-posY == (i-j) && (*matrix)[i][j] == 8 && i != posX && j != posY) || (posX+posY == (i+j) && (*matrix)[i][j] == 8 && i != posX && j != posY) {
				validator = true
				break
			}
			//sum += 2
		}
	}
	//sum = refMain + 2
	fck := posX + posY
	if validator {
		for i := 0; i < LINE; i++ {
			for j := 0; j < COLUMN; j++ {
				if refMain == (i-j) && (*matrix)[i][j] != 8 {
					(*matrix)[i][j] = 1
				}
				if posX-posY == (i-j) && (*matrix)[i][j] != 8 && i != posX && j != posY {
					(*matrix)[i][j] = 1
					//sum += 2
				}
				if fck == (i+j) && (*matrix)[i][j] != 8 && i != posX && j != posY {
					(*matrix)[i][j] = 1

				}
			}

		}

	}
	checkHeuristics(matrix, posX, posY)
}

func checkHeuristics(matrix *[][]int, posX, posY int) {
	counter := 0
	for i := 0; i < LINE; i++ {
		for j := 0; j < COLUMN; j++ {
			if (*matrix)[i][j] == 0 {
				counter++
			}
		}
	}
	heuristics[fmt.Sprintf("%d+%d", posX, posY)] = counter
	printMatrix(matrix)
	fmt.Println("Heuristics ", heuristics)

}

func main() {
	matrix := make([][]int, LINE)
	createMatrix(&matrix)
	matrix[3][3] = 8
	checkColumn(&matrix, 3)
	checkLine(&matrix, 3)
	checkDiagonal(&matrix, 3, 3)
}
