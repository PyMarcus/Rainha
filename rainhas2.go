package main

import "fmt"

const LINE int = 4
const COLUMN int = 4

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

	printMatrix(matrix)
}

func main() {
	matrix := make([][]int, LINE)
	createMatrix(&matrix)
	matrix[0][2] = 8
	checkColumn(&matrix, 0)
	checkLine(&matrix, 2)
}
