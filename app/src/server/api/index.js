import { Router } from 'express';
import bodyParser from 'body-parser';

import health from './health';
import my from './my';
import listings from './listings';
import offers from './offers';
import subscriptions from './subscriptions';
import users from './users';

const router = Router();

router.use(bodyParser.json());

router.get('/metrics/health', health);
router.get('/my', my);
router.use('/listings', listings);
router.use('/offers', offers);
router.use('/subscriptions', subscriptions);
router.use('/users', users);

router.use((error, req, res, next) => {
  res.status(500).json({
    error: error.message,
  });
});

export default router;
