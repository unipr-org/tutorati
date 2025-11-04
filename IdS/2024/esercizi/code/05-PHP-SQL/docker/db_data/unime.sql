-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: web-server-db:3306
-- Creato il: Nov 10, 2024 alle 18:26
-- Versione del server: 9.1.0
-- Versione PHP: 8.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `unime`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `courses`
--

CREATE TABLE `courses` (
  `id` int NOT NULL,
  `course_name` varchar(50) NOT NULL,
  `course_description` text NOT NULL,
  `course_year` varchar(100) NOT NULL,
  `course_image` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Dump dei dati per la tabella `courses`
--

INSERT INTO `courses` (`id`, `course_name`, `course_description`, `course_year`, `course_image`) VALUES
(1, 'Programmazione A', 'Corso di programmazione di base', 'Anno 1', '/assets/img/courses/progA.jpg'),
(2, 'Algebra', 'Corso di algebra lineare', 'Anno 1', '/assets/img/courses/algebra.jpg'),
(3, 'Intelligenza Artificiale', 'Corso di intelligenza artificiale', 'Anno 3', '/assets/img/courses/ai.jpg'),
(4, 'Programmazione B', 'Corso di programmazione avanzata', 'Anno 2', '/assets/img/courses/progA.jpg');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `courses`
--
ALTER TABLE `courses`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `courses`
--
ALTER TABLE `courses`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;