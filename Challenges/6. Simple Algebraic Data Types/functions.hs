import Data.Either
import Data.Maybe


eitherFromMaybe :: Maybe a -> Either () a
eitherFromMaybe (Just x) = Right x
eitherFromMaybe Nothing = Left ()

maybeFromEither :: Either () a -> Maybe a
maybeFromEither (Right x) = Just x
maybeFromEither (Left ()) = Nothing