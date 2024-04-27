CREATE DATABASE Project_3;

USE Project_3;

CREATE TABLE job_data( ds VARCHAR(20), job_id int, actor_id int, `event` VARCHAR(20), `language` VARCHAR(20), time_spent int, org VARCHAR(5));

INSERT INTO job_data (ds, job_id, actor_id, `event`, `language`, time_spent, org)
VALUES
('2020-11-30', 121, 1001, 'skip', 'English', 20, 'A'), ('2020-11-30', 122, 1006, 'transfer', 'Arabic', 29, 'B'), ('2020-11-29', 123, 1003, 'decision', 'Persian', 18, 'C'), ('2020-11-28', 123, 1005, 'transfer', 'Persian', 24, 'D'), ('2020-11-28', 125, 1002, 'decision', 'Hindi', 16, 'B'), ('2020-11-27', 11, 1007, 'decision', 'French', 96, 'D'),
('2020-11-26', 23, 1004, 'skip', 'Persian', 60, 'A'),
('2020-11-25', 20, 1003, 'transfer', 'Italian', 47, 'C'),
('2020-12-01', 22, 1001, 'skip', 'English', 17, 'A'),
('2020-11-30', 23, 1006, 'transfer', 'Arabic', 27, 'B'),
('2020-11-29', 24, 1003, 'decision', 'Persian', 19, 'C'),
('2020-11-28', 24, 1005, 'transfer', 'Persian', 21, 'D'),
('2020-11-28', 26, 1002, 'decision', 'Hindi', 10, 'B'),
('2020-11-27', 12, 1007, 'decision', 'French', 102, 'D'),
('2020-11-26', 24, 1004, 'skip', 'Persian', 54, 'A'),
('2020-11-25', 21, 1003, 'transfer', 'Italian', 43, 'C'),
('2020-12-02', 22, 1001, 'skip', 'English', 16, 'A'),
('2020-12-01', 23, 1006, 'transfer', 'Arabic', 24, 'B'),
('2020-11-30', 24, 1003, 'decision', 'Persian', 22, 'C'),
('2020-11-29', 25, 1005, 'transfer', 'Persian', 23, 'D'),
('2020-11-29', 27, 1002, 'decision', 'Hindi', 13, 'B'),
('2020-11-28', 13, 1007, 'decision', 'French', 99, 'D'),
('2020-11-27', 25, 1004, 'skip', 'Persian', 58, 'A'),
('2020-11-26', 22, 1003, 'transfer', 'Italian', 46, 'C'),
('2020-12-03', 21, 1001, 'skip', 'English', 18, 'A'),
('2020-12-02', 22, 1006, 'transfer', 'Arabic', 26, 'B'),
('2020-12-01', 23, 1003, 'decision', 'Persian', 21, 'C'),
('2020-11-30', 23, 1005, 'transfer', 'Persian', 25, 'D'),
('2020-11-30', 25, 1002, 'decision', 'Hindi', 12, 'B'),
('2020-11-29', 11, 1007, 'decision', 'French', 105, 'D'),
('2020-11-28', 25, 1004, 'skip', 'Persian', 57, 'A'),
('2020-11-27', 22, 1003, 'transfer', 'Italian', 44, 'C'),
('2020-12-04', 23, 1001, 'skip', 'English', 19, 'A'),
('2020-12-03', 24, 1006, 'transfer', 'Arabic', 30, 'B'),
('2020-12-02', 25, 1003, 'decision', 'Persian', 20, 'C'),
('2020-12-01', 25, 1005, 'transfer', 'Persian', 22, 'D'),
('2020-12-01', 27, 1002, 'decision', 'Hindi', 11, 'B'),
('2020-11-30', 13, 1007, 'decision', 'French', 101, 'D'),
('2020-11-29', 26, 1004, 'skip', 'Persian', 55, 'A'),
('2020-11-28', 23, 1003, 'transfer', 'Italian', 42, 'C'),
('2020-12-05', 24, 1001, 'skip', 'English', 22, 'A'),
('2020-12-04', 25, 1006, 'transfer', 'Arabic', 28, 'B'),
('2020-12-03', 23, 1003, 'decision', 'Persian', 23, 'C'),
('2020-12-02', 24, 1005, 'transfer', 'Persian', 20, 'D'),
('2020-12-02', 26, 1002, 'decision', 'Hindi', 9, 'B'),
('2020-12-01', 14, 1007, 'decision', 'French', 98, 'D'),
('2020-11-30', 26, 1004, 'skip', 'Persian', 59, 'A'), ('2020-11-29', 22, 1003, 'transfer', 'Italian', 41, 'C'), ('2020-12-06', 25, 1001, 'skip', 'English', 21, 'A'), ('2020-12-05', 26, 1006, 'transfer', 'Arabic', 27, 'B');

SET SQL_SAFE_UPDATES = 0;


SELECT * from job_data;
UPDATE job_data
SET ds = '2020-11-24'   
WHERE ds = '2020-11-17';

SELECT COUNT(*) FROM job_data;
INSERT INTO job_data (ds, job_id, actor_id, `event`, `language`, time_spent, org)
VALUES
('2020-11-13', 121, 1008, 'skip', 'English', 25, 'B'), ('2020-11-13', 122, 1005, 'transfer', 'Arabic', 19, 'B'), ('2020-11-19', 124, 1003, 'decision', 'Persian', 88, 'C'), ('2020-11-08', 124, 1002, 'transfer', 'Persian', 24, 'A'), ('2020-11-08', 125, 1002, 'decision', 'Hindi', 36, 'C'), ('2020-11-17', 12, 1007, 'decision', 'French', 16, 'D');

with duplicate_rows AS (SELECT *, row_number() over(partition by ds, job_id, actor_id, `event`, `language`, time_spent, org) as checking from job_data)
select * from duplicate_rows where checking > 1;

SELECT ds, COUNT(job_id)/(SUM(time_spent)/3600) AS jobs_per_hour_per_day
FROM job_data 
WHERE 
    ds LIKE '%-11-%' 
GROUP BY ds
ORDER BY ds;

select * from job_data order by actor_id;

select count(`language`) from job_data group by `language`;
with SUM_table AS (select count(`language`) as total_language from job_data)
select job_data.`language`, (count(job_data.`language`)/SUM_table.total_language) as percentage from job_data, SUM_table group by job_data.`language`, SUM_table.total_language;

SELECT ds, COUNT(job_id)/(SUM(time_spent)) AS throughput OVER(ORDER BY ds ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS rolling;

CREATE VIEW throughput__table AS (SELECT ds, COUNT(*) AS throughput
  FROM
      job_data
  WHERE
      ds LIKE '%-11-%'
  GROUP BY
      ds);
SELECT ds, AVG(throughput) OVER (ORDER BY ds ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS 7_day_rolling_average
FROM 
    throughput__table
ORDER BY
    ds;
SELECT ds, throughput, avg(throughput) OVER(ORDER BY ds ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS rolling FROM throughput_;


SELECT
  DATE(ds) AS date,
  HOUR(ds) AS hour,
  COUNT(DISTINCT job_id) AS jobs_reviewed
FROM
  job_data
WHERE
  MONTH(ds) = 11 AND YEAR(ds) = 2020
GROUP BY
  DATE(ds),
  HOUR(ds)
ORDER BY
  date,
  hour;