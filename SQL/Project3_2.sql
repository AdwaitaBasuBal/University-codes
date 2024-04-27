CREATE DATABASE Project_3_CS_2;

use Project_3_CS_2;

CREATE TABLE users(user_id int UNIQUE PRIMARY KEY, created_at TIMESTAMP DEFAULT NOW(), company_id int, `language` VARCHAR(20), activated_at VARCHAR(20) DEFAULT NULL, state VARCHAR(20));

CREATE TABLE `events`(user_id int, occured_at TIMESTAMP DEFAULT NOW(), event_type VARCHAR(30), event_name VARCHAR(30), location VARCHAR(30), device VARCHAR(30));
select * from users;
select * from `events`;
select * from `email_events`;

CREATE TABLE `email_events`(user_id int, occured_at TIMESTAMP DEFAULT NOW(), `action` VARCHAR(30));
ALTER TABLE `events`
      ADD CONSTRAINT fk_user_id
      FOREIGN KEY (user_id) REFERENCES users(user_id);

ALTER TABLE `email_events`
      ADD CONSTRAINT fk_email_user_id
      FOREIGN KEY (user_id) REFERENCES users(user_id);


show variables like 'sql_mode';

WITH cohort_summary AS (
    SELECT
        WEEK(us.created_at) AS cohort_week,
        WEEK(e.occured_at) AS engagement_week,
        COUNT(DISTINCT e.user_id) AS engaged_users,
        COUNT(DISTINCT us.user_id) AS cohort_size,
        (engaged_users / cohort_size) * 100 AS retention_rate
    FROM
        users us
    LEFT JOIN
        `events` e ON us.user_id = e.user_id
            AND WEEK(e.occured_at) >= WEEK(us.created_at)
    WHERE us.state = 'active'
    GROUP BY
        cohort_week,
        engagement_week
)
SELECT
    cohort_week,
    engagement_week,
    engaged_users,
    (engaged_users / cohort_size) * 100 AS retention_rate
FROM
    cohort_summary;
    
WITH cohort_summary AS (
    SELECT
        WEEK(us.created_at) AS cohort_week,
        WEEK(e.occured_at) AS engagement_week,
        COUNT(DISTINCT CASE WHEN WEEK(e.occured_at) = WEEK(us.created_at) THEN e.user_id END) AS cohort_size,
        COUNT(DISTINCT e.user_id) AS engaged_users
    FROM
        users us
    LEFT JOIN
        `events` e ON us.user_id = e.user_id
            AND WEEK(e.occured_at) >= WEEK(us.created_at)
	WHERE us.state = 'active'
    GROUP BY
        cohort_week,
        engagement_week
)
SELECT
    cohort_week,
    engagement_week,
    engaged_users,
    (engaged_users / cohort_size) * 100 AS retention_rate
FROM
    cohort_summary;
    
SELECT
    WEEK(e1.occured_at) AS engagement_week,
    COUNT(DISTINCT e1.user_id) AS engaged_users,
    COUNT(DISTINCT e2.user_id) AS cohort_size,
    (COUNT(DISTINCT e1.user_id) / COUNT(DISTINCT e2.user_id)) * 100 AS retention_rate
FROM
    `events` e1
LEFT JOIN
    `events` e2 ON e1.user_id = e2.user_id
        AND WEEK(e1.occured_at) = WEEK(e2.occured_at)
        AND e2.event_type = 'signup_flow'
WHERE 
    e1.event_type = 'engagement'
GROUP BY
    engagement_week;
    
SELECT
    engagement_week,
    engaged_users,
    cohort_size,
    (engaged_users / cohort_size) * 100 AS retention_rate
FROM
    (
        SELECT
            WEEK(e1.occured_at) AS engagement_week,
            COUNT(DISTINCT e1.user_id) AS engaged_users
        FROM
            `events` e1
        WHERE
            e1.event_type = 'engagement'
        GROUP BY
            engagement_week
    ) e
LEFT JOIN
    (
        SELECT
            WEEK(e2.occured_at) AS cohort_week,
            COUNT(DISTINCT e2.user_id) AS cohort_size
        FROM
            `events` e2
        WHERE
            e2.event_type = 'signup_flow'
        GROUP BY
            cohort_week
    ) s ON e.engagement_week = s.cohort_week;

WITH user_cohort AS (
    SELECT
        user_id,
        MIN(occured_at) AS sign_up_date
    FROM
        events
    WHERE
        event_type = 'signup_flow'
    GROUP BY
        user_id
),
cohort_summary AS (
    SELECT
        uc.sign_up_date,
        WEEK(e.occured_at) AS engagement_week,
        COUNT(DISTINCT e.user_id) AS engaged_users,
        COUNT(DISTINCT uc.user_id) AS cohort_size
    FROM
        user_cohort uc
    LEFT JOIN
        events e ON uc.user_id = e.user_id
            AND WEEK(e.occured_at) >= WEEK(uc.sign_up_date)
    WHERE
        e.event_type = 'engagement'
    GROUP BY
        uc.sign_up_date,
        engagement_week
)
SELECT
    sign_up_date,
    engagement_week,
    engaged_users,
    cohort_size,
    (engaged_users / cohort_size) * 100 AS retention_rate
FROM
    cohort_summary;
    
SELECT
distinct user_id,
COUNT(user_id),
SUM(CASE WHEN retention_week = 1 Then 1 Else 0 END) as per_week_retention
FROM
(
SELECT
a.user_id, a.signup_week,
b.engagement_week,
b.engagement_week - a.signup_week as retention_week
FROM
(
(SELECT distinct user_id, extract(week from occured_at) as signup_week from `events` WHERE event_type = 'signup_flow'
and event_name = 'complete_signup'
)a
LEFT JOIN
(SELECT distinct user_id, extract(week from occured_at) as engagement_week FROM `events` where event_type = 'engagement'
)b
on a.user_id = b.user_id)
)d
group by user_id
order by user_id;

SELECT YEAR(u.created_at) AS `year`, WEEK(u.created_at) AS `week`, COUNT(DISTINCT u.user_id) AS sign_up, COUNT(DISTINCT e.user_id) AS retained  FROM `events` e JOIN `users` u ON e.user_id = u.user_id WHERE  e.event_type = 'engagement' AND u.`state` = 'active' AND e.user_id = u.user_id GROUP BY `year`,`week` ;

SELECT DISTINCT u.user_id, e.user_id FROM `events` e cross JOIN `users` u ON e.user_id = u.user_id WHERE e.event_type = 'engagement' AND u.`state` = 'active' AND week(u.created_at) = 0;

SELECT
  YEAR(u.created_at) AS `year`,
  WEEK(u.created_at) AS `week`,
  COUNT(DISTINCT u.user_id) AS sign_up,
  COUNT(DISTINCT e.user_id) AS retained
FROM
  `users` u
LEFT JOIN
  `events` e ON e.user_id = u.user_id AND e.event_type = 'engagement'
WHERE
  u.`state` = 'active' AND e.user_id IS NOT NULL
GROUP BY
  `year`, `week`;
  
SELECT
  YEAR(u.created_at) AS `year`,
  WEEK(u.created_at) AS `week`,
  (COUNT(DISTINCT u.user_id) OVER(ORDER BY `week` ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)/
  LAG(COUNT(DISTINCT e.user_id))) * 100 AS retain_percentage
FROM
  `users` u
LEFT JOIN
  `events` e ON e.user_id = u.user_id
WHERE
 e.event_type = 'engagement' AND e.user_id IS NOT NULL
GROUP BY
  `year`, `week`;
  
SELECT
  YEAR(u.created_at) AS `year`,
  WEEK(u.created_at) AS `week`,
  COUNT(DISTINCT u.user_id) AS total_users,
  (COUNT(DISTINCT e.user_id) * 100 / 
      LAG(COUNT(DISTINCT u.user_id)) OVER (ORDER BY WEEK(u.created_at) ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW)) AS retain_percentage
FROM
  `users` u
LEFT JOIN
  `events` e ON e.user_id = u.user_id
WHERE
  e.event_type = 'engagement' AND e.user_id IS NOT NULL
GROUP BY
  `year`, `week`
ORDER BY
  `year`, `week`;


  