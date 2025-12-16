<?php
abstract class Gateway {
    abstract public function handle_request($parts);
}
